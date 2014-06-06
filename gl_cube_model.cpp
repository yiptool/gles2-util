/* vim: set ai noet ts=4 sw=4 tw=115: */
//
// Copyright (c) 2014 Nikolay Zapolnov (zapolnov@gmail.com).
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#include "gl_cube_model.h"
#include "gl_buffer_binder.h"
#include <yip-imports/cxx-util/macros.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <memory>

GL::CubeModel::CubeModel(ResourceManager * resMgr, float size, bool inside, const std::string & resName)
	: Model(resMgr, resName)
{
	const float S = size * 0.5f;
	const float N = (inside ? -1.0f : 1.0f);

	Model::Vertex vertices[] =
	{
		// Position     | TexCoord | Normal        | Tangent       | Binormal
		// Top
		{ { -S, -S, -S }, { 0, 0 }, {  0, -N,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 0
		{ { -S, -S,  S }, { 0, 1 }, {  0, -N,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 1
		{ {  S, -S,  S }, { 1, 1 }, {  0, -N,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 2
		{ {  S, -S, -S }, { 1, 0 }, {  0, -N,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 3
		// Left
		{ { -S,  S,  S }, { 0, 0 }, { -N,  0,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 4
		{ { -S, -S,  S }, { 0, 1 }, { -N,  0,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 5
		{ { -S, -S, -S }, { 1, 1 }, { -N,  0,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 6
		{ { -S,  S, -S }, { 1, 0 }, { -N,  0,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 7
		// Right
		{ {  S,  S, -S }, { 0, 0 }, {  N,  0,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 8
		{ {  S, -S, -S }, { 0, 1 }, {  N,  0,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 9
		{ {  S, -S,  S }, { 1, 1 }, {  N,  0,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 10
		{ {  S,  S,  S }, { 1, 0 }, {  N,  0,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 11
		// Bottom
		{ {  S,  S, -S }, { 0, 0 }, {  0,  N,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 12
		{ {  S,  S,  S }, { 0, 1 }, {  0,  N,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 13
		{ { -S,  S,  S }, { 1, 1 }, {  0,  N,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 14
		{ { -S,  S, -S }, { 1, 0 }, {  0,  N,  0 }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 15
		// Near
		{ { -S,  S, -S }, { 0, 0 }, {  0,  0, -N }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 16
		{ { -S, -S, -S }, { 0, 1 }, {  0,  0, -N }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 17
		{ {  S, -S, -S }, { 1, 1 }, {  0,  0, -N }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 18
		{ {  S,  S, -S }, { 1, 0 }, {  0,  0, -N }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 19
		// Far
		{ {  S,  S,  S }, { 0, 0 }, {  0,  0,  N }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 20
		{ {  S, -S,  S }, { 0, 1 }, {  0,  0,  N }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 21
		{ { -S, -S,  S }, { 1, 1 }, {  0,  0,  N }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 22
		{ { -S,  S,  S }, { 1, 0 }, {  0,  0,  N }, { 0, 0, 0, 0 }, { 0, 0, 0 } },		// 23
	};

	for (unsigned i = 0; i < 24; i += 4)
	{
		float deltaPos1x = vertices[i + 1].position[0] - vertices[i].position[0];
		float deltaPos1y = vertices[i + 1].position[1] - vertices[i].position[1];
		float deltaPos1z = vertices[i + 1].position[2] - vertices[i].position[2];

		float deltaPos2x = vertices[i + 2].position[0] - vertices[i].position[0];
		float deltaPos2y = vertices[i + 2].position[1] - vertices[i].position[1];
		float deltaPos2z = vertices[i + 2].position[2] - vertices[i].position[2];

		float deltaUV1x = vertices[i + 1].texCoord[0] - vertices[i].texCoord[0];
		float deltaUV1y = vertices[i + 1].texCoord[1] - vertices[i].texCoord[1];

		float deltaUV2x = vertices[i + 2].texCoord[0] - vertices[i].texCoord[0];
		float deltaUV2y = vertices[i + 2].texCoord[1] - vertices[i].texCoord[1];

		float r = 1.0f / (deltaUV1x * deltaUV2y - deltaUV1y * deltaUV2x);
		float tanx = (deltaPos1x * deltaUV2y - deltaPos2x * deltaUV1y) * r;
		float tany = (deltaPos1y * deltaUV2y - deltaPos2y * deltaUV1y) * r;
		float tanz = (deltaPos1z * deltaUV2y - deltaPos2z * deltaUV1y) * r;

		float bitanx = (deltaPos2x * deltaUV1x - deltaPos1x * deltaUV2x) * r;
		float bitany = (deltaPos2y * deltaUV1x - deltaPos1y * deltaUV2x) * r;
		float bitanz = (deltaPos2z * deltaUV1x - deltaPos1z * deltaUV2x) * r;

		// Setting tangent
		vertices[i].tangent[0] = tanx;
		vertices[i].tangent[1] = tany;
		vertices[i].tangent[2] = tanz;

		vertices[i + 1].tangent[0] = tanx;
		vertices[i + 1].tangent[1] = tany;
		vertices[i + 1].tangent[2] = tanz;

		vertices[i + 2].tangent[0] = tanx;
		vertices[i + 2].tangent[1] = tany;
		vertices[i + 2].tangent[2] = tanz;

		vertices[i + 3].tangent[0] = tanx;
		vertices[i + 3].tangent[1] = tany;
		vertices[i + 3].tangent[2] = tanz;

		// Setting bitangent
		vertices[i].binormal[0] = bitanx;
		vertices[i].binormal[1] = bitany;
		vertices[i].binormal[2] = bitanz;

		vertices[i + 1].binormal[0] = bitanx;
		vertices[i + 1].binormal[1] = bitany;
		vertices[i + 1].binormal[2] = bitanz;

		vertices[i + 2].binormal[0] = bitanx;
		vertices[i + 2].binormal[1] = bitany;
		vertices[i + 2].binormal[2] = bitanz;

		vertices[i + 3].binormal[0] = bitanx;
		vertices[i + 3].binormal[1] = bitany;
		vertices[i + 3].binormal[2] = bitanz;
	}

	std::vector<GL::UByte> indices;
	if (inside)
	{
		indices = {
			 0,  1,  2,  0,  2,  3,		// Top
			 4,  5,  6,  4,  6,  7,		// Left
			 8,  9, 10,  8, 10, 11,		// Right
			12, 13, 14, 12, 14, 15,		// Bottom
			16, 17, 18, 16, 18, 19,		// Near
			20, 21, 22, 20, 22, 23,		// Far
		};
	}
	else
	{
		indices = {
			 2,  1,  0,  3,  2,  0,		// Top
			 6,  5,  4,  7,  6,  4,		// Left
			10,  9,  8, 11, 10,  8,		// Right
			14, 13, 12, 15, 14, 12,		// Bottom
			18, 17, 16, 19, 18, 16,		// Near
			22, 21, 20, 23, 22, 20,		// Far
		};
	}

	setCenter(0.0f, 0.0f, 0.0f);
	setSize(size, size, size);
	setRadius(S);

	setNumTriangles(int(indices.size() / 3));
	setNumVertices(int(sizeof(vertices) / sizeof(vertices[0])));

	{
		GL::BufferBinder binder(vertexBuffer(), GL::ARRAY_BUFFER);
		GL::bufferData(GL::ARRAY_BUFFER, sizeof(vertices), vertices, GL::STATIC_DRAW);
	}

	{
		GL::BufferBinder binder(indexBuffer(), GL::ELEMENT_ARRAY_BUFFER);
		GL::bufferData(GL::ELEMENT_ARRAY_BUFFER, Sizei(indices.size()), indices.data(), GL::STATIC_DRAW);
		setIndexType(GL::UNSIGNED_BYTE);
	}

	setNumMaterials(1);
	material(0).initWithDefaults();

	setNumMeshes(1);
	mesh(0).init(&material(0), 0, Int(indices.size()));
}
