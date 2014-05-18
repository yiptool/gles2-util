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
#include "gl_model.h"
#include "gl_resource_manager.h"
#include "gl_buffer_binder.h"
#include <yip-imports/cxx-util/macros.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <memory>

void GL::Model::Material::initWithDefaults()
{
	ambient[0] = 0.0f;
	ambient[1] = 0.0f;
	ambient[2] = 0.0f;
	ambient[3] = 1.0f;

	diffuse[0] = 1.0f;
	diffuse[1] = 1.0f;
	diffuse[2] = 1.0f;
	diffuse[3] = 1.0f;

	specular[0] = 0.0f;
	specular[1] = 0.0f;
	specular[2] = 0.0f;
	specular[3] = 1.0f;

	shininess = 0.0f;
	opacity = 1.0f;

	texture.reset();
	normalMap.reset();
}

GL::Model::Model(ResourceManager * resMgr, const std::string & resName)
	: Resource(resMgr, resName),
	  m_IndexType(GL::UNSIGNED_SHORT),
	  m_Radius(0.0f),
	  m_NumTriangles(0),
	  m_NumVertices(0)
{
	setCenter(0.0f, 0.0f, 0.0f);
	setSize(0.0f, 0.0f, 0.0f);
	m_Vertices = resMgr->createBuffer(resName);
	m_Indices = resMgr->createBuffer(resName);
}

void GL::Model::bindVertexBuffer(int aPos, int aTexCoord, int aNorm, int aTangent, int aBinorm) const
{
	#define OFF(X) ((void *)offsetof(Vertex, X))

	GL::BufferBinder binder(m_Vertices, GL::ARRAY_BUFFER);
	Sizei stride = Sizei(sizeof(Vertex));

	if (aPos >= 0)
		GL::vertexAttribPointer(aPos, 3, GL::FLOAT, GL::FALSE, stride, OFF(position));
	if (aTexCoord >= 0)
		GL::vertexAttribPointer(aTexCoord, 2, GL::FLOAT, GL::FALSE, stride, OFF(texCoord));
	if (aNorm >= 0)
		GL::vertexAttribPointer(aNorm, 3, GL::FLOAT, GL::TRUE, stride, OFF(normal));
	if (aTangent >= 0)
		GL::vertexAttribPointer(aTangent, 4, GL::FLOAT, GL::FALSE, stride, OFF(tangent));
	if (aBinorm >= 0)
		GL::vertexAttribPointer(aBinorm, 3, GL::FLOAT, GL::FALSE, stride, OFF(binormal));

	#undef OFF
}

void GL::Model::drawMesh(int index) const
{
	const Mesh & mesh = m_Meshes[index];

	size_t step = 0;
	switch (m_IndexType)
	{
	case GL::UNSIGNED_BYTE: step = sizeof(UByte); break;
	case GL::UNSIGNED_SHORT: step = sizeof(UShort); break;
	case GL::UNSIGNED_INT: step = sizeof(UInt); break;
	default: throw std::runtime_error("indices have invalid type.");
	}

	GL::drawElements(GL::TRIANGLES, mesh.numIndices, m_IndexType, (void *)(mesh.firstIndex * step));
}

void GL::Model::destroy()
{
	m_Indices->destroy();
	m_Vertices->destroy();
	m_Meshes.clear();
	m_Materials.clear();
	setCenter(0.0f, 0.0f, 0.0f);
	setSize(0.0f, 0.0f, 0.0f);
	m_Radius = 0.0f;
	m_NumTriangles = 0;
	m_NumVertices = 0;
}
