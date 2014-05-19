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
#include "gl_obj_model.h"
#include "gl_resource_manager.h"
#include "gl_buffer_binder.h"
#include <yip-imports/cxx-util/macros.h>
#include <yip-imports/model_obj.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <memory>
#include <algorithm>

GL::ObjModel::ObjModel(ResourceManager * resMgr, ::Resource::Loader & loader, const std::string & filename)
	: Model(resMgr, filename)
{
	ModelOBJ model;
	model.import(loader, filename);

	float x = 0.0f, y = 0.0f, z = 0.0f;
	model.getCenter(x, y, z);
	setCenter(x, y, z);

	setSize(model.getWidth(), model.getHeight(), model.getLength());
	setRadius(model.getRadius());
	setNumTriangles(model.getNumberOfTriangles());
	setNumVertices(model.getNumberOfVertices());

	m_HasNormals = model.hasNormals() ? 1 : 0;
	m_HasPositions = model.hasPositions() ? 1 : 0;
	m_HasTangents = model.hasTangents() ? 1 : 0;
	m_HasTexCoords = model.hasTextureCoords() ? 1 : 0;

	STATIC_ASSERT(sizeof(Vertex) == sizeof(ModelOBJ::Vertex));
	STATIC_ASSERT(sizeof(int) == sizeof(Int));
	STATIC_ASSERT(sizeof(float) == sizeof(Float));

	{
		GL::BufferBinder binder(vertexBuffer(), GL::ARRAY_BUFFER);
		GL::bufferData(GL::ARRAY_BUFFER, model.getNumberOfVertices() * model.getVertexSize(),
			model.getVertexBuffer(), GL::STATIC_DRAW);
	}

	{
		GL::BufferBinder binder(indexBuffer(), GL::ELEMENT_ARRAY_BUFFER);
		if (model.getNumberOfVertices() < 0xFF)
		{
			std::vector<GL::UByte> data(model.getNumberOfIndices());
			for (int i = 0; i < model.getNumberOfIndices(); i++)
				data[i] = static_cast<GL::UByte>(model.getIndexBuffer()[i]);
			GL::bufferData(GL::ELEMENT_ARRAY_BUFFER, Sizei(data.size()), data.data(), GL::STATIC_DRAW);
			setIndexType(GL::UNSIGNED_BYTE);
		}
		else if (model.getNumberOfVertices() < 0xFFFF)
		{
			std::vector<GL::UShort> data(model.getNumberOfIndices());
			for (int i = 0; i < model.getNumberOfIndices(); i++)
				data[i] = static_cast<GL::UShort>(model.getIndexBuffer()[i]);
			GL::bufferData(GL::ELEMENT_ARRAY_BUFFER, Sizei(data.size() * sizeof(GL::UShort)),
				data.data(), GL::STATIC_DRAW);
			setIndexType(GL::UNSIGNED_SHORT);
		}
		else
		{
			GL::bufferData(GL::ELEMENT_ARRAY_BUFFER, model.getNumberOfIndices() * model.getIndexSize(),
				model.getIndexBuffer(), GL::STATIC_DRAW);
			setIndexType(GL::UNSIGNED_INT);
		}
	}

	setNumMaterials(model.getNumberOfMaterials());
	for (int i = 0; i < model.getNumberOfMaterials(); i++)
	{
		const ModelOBJ::Material & m = model.getMaterial(i);
		Material & mat = material(i);

	  #ifdef HAVE_GLM
		mat.ambient = glm::vec4(m.ambient[0], m.ambient[1], m.ambient[2], m.ambient[3]);
		mat.diffuse = glm::vec4(m.diffuse[0], m.diffuse[1], m.diffuse[2], m.diffuse[3]);
		mat.specular = glm::vec4(m.specular[0], m.specular[1], m.specular[2], m.specular[3]);
	  #else
		std::copy(&m.ambient[0], m.ambient + sizeof(m.ambient) / sizeof(m.ambient[0]), &mat.ambient[0]);
		std::copy(&m.diffuse[0], m.diffuse + sizeof(m.diffuse) / sizeof(m.diffuse[0]), &mat.diffuse[0]);
		std::copy(&m.specular[0], m.specular + sizeof(m.specular) / sizeof(m.specular[0]), &mat.specular[0]);
	  #endif
		mat.shininess = m.shininess;
		mat.opacity = m.alpha;

		if (m.colorMapFilename.length() > 0)
			mat.texture = manager()->getTexture(m.colorMapFilename);
		if (m.bumpMapFilename.length() > 0)
			mat.normalMap = manager()->getTexture(m.bumpMapFilename);
	}

	if (model.getNumberOfMaterials() == 0)
	{
		setNumMaterials(1);
		material(0).initWithDefaults();
	}

	setNumMeshes(model.getNumberOfMeshes());
	for (int i = 0; i < model.getNumberOfMeshes(); i++)
	{
		const ModelOBJ::Mesh & m = model.getMesh(i);
		Mesh & mm = mesh(i);

		mm.firstIndex = m.startIndex;
		mm.numIndices = m.triangleCount * 3;
		mm.material = &material(std::min(std::max(m.materialIndex, 0), int(numMaterials())));
	}
}
