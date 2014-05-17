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

GL::ObjModel::ObjModel(ResourceManager * resMgr, ::Resource::Loader & loader, const std::string & filename)
	: Resource(resMgr, filename)
{
	ModelOBJ model;
	model.import(loader, filename);
	model.getCenter(m_Center[0], m_Center[1], m_Center[2]);
	m_Size[0] = model.getWidth();
	m_Size[1] = model.getHeight();
	m_Size[2] = model.getLength();
	m_Radius = model.getRadius();
	m_NumTriangles = model.getNumberOfTriangles();
	m_NumVertices = model.getNumberOfVertices();
	m_HasNormals = model.hasNormals() ? 1 : 0;
	m_HasPositions = model.hasPositions() ? 1 : 0;
	m_HasTangents = model.hasTangents() ? 1 : 0;
	m_HasTexCoords = model.hasTextureCoords() ? 1 : 0;

	STATIC_ASSERT(sizeof(int) == sizeof(Int));
	STATIC_ASSERT(sizeof(float) == sizeof(Float));

	m_Vertices = resMgr->createBuffer(filename);
	{
		GL::BufferBinder binder(m_Vertices, GL::ARRAY_BUFFER);
		GL::bufferData(GL::ARRAY_BUFFER, model.getNumberOfVertices() * model.getVertexSize(),
			model.getVertexBuffer(), GL::STATIC_DRAW);
	}

	m_Indices = resMgr->createBuffer(filename);
	{
		GL::BufferBinder binder(m_Indices, GL::ELEMENT_ARRAY_BUFFER);
		GL::bufferData(GL::ELEMENT_ARRAY_BUFFER, model.getNumberOfIndices() * model.getIndexSize(),
			model.getIndexBuffer(), GL::STATIC_DRAW);
	}

	m_Materials.resize(model.getNumberOfMaterials());
	for (int i = 0; i < model.getNumberOfMaterials(); i++)
	{
		const ModelOBJ::Material & m = model.getMaterial(i);
		Material & material = m_Materials[i];

	  #ifdef HAVE_GLM
		material.ambient = glm::vec4(m.ambient[0], m.ambient[1], m.ambient[2], m.ambient[3]);
		material.diffuse = glm::vec4(m.diffuse[0], m.diffuse[1], m.diffuse[2], m.diffuse[3]);
		material.specular = glm::vec4(m.specular[0], m.specular[1], m.specular[2], m.specular[3]);
	  #else
		std::copy(&m.ambient[0], m.ambient + sizeof(m.ambient) / sizeof(m.ambient[0]), &material.ambient[0]);
		std::copy(&m.diffuse[0], m.diffuse + sizeof(m.diffuse) / sizeof(m.diffuse[0]), &material.diffuse[0]);
		std::copy(&m.specular[0], m.specular + sizeof(m.specular) / sizeof(m.specular[0]), &material.specular[0]);
	  #endif
		material.shininess = m.shininess;
		material.opacity = m.alpha;

		if (m.colorMapFilename.length() > 0)
			material.texture = manager()->getTexture(m.colorMapFilename);
		if (m.bumpMapFilename.length() > 0)
			material.bumpMap = manager()->getTexture(m.bumpMapFilename);

		m_Materials[i] = std::move(material);
	}

	m_Meshes.resize(model.getNumberOfMeshes());
	for (int i = 0; i < model.getNumberOfMeshes(); i++)
	{
		const ModelOBJ::Mesh & m = model.getMesh(i);
		Mesh & mesh = m_Meshes[i];

		mesh.firstIndex = m.startIndex;
		mesh.numIndices = m.triangleCount * 3;
		mesh.material = &m_Materials[m.materialIndex];
	}
}

void GL::ObjModel::destroy()
{
	m_Indices->destroy();
	m_Vertices->destroy();
	m_Meshes.clear();
	m_Materials.clear();
}

void GL::ObjModel::bindVertexBuffer(int aPos, int aTexCoord, int aNorm, int aTangent, int aBinorm) const
{
	#define OFF(X) ((void *)offsetof(ModelOBJ::Vertex, X))
	GL::bindBuffer(GL::ARRAY_BUFFER, m_Vertices->handle());

	Sizei stride = Sizei(sizeof(ModelOBJ::Vertex));
	if (aPos >= 0)
		GL::vertexAttribPointer(aPos, 3, GL::FLOAT, GL::FALSE, stride, OFF(position));
	if (aTexCoord >= 0)
		GL::vertexAttribPointer(aTexCoord, 2, GL::FLOAT, GL::FALSE, stride, OFF(texCoord));
	if (aNorm >= 0)
		GL::vertexAttribPointer(aNorm, 3, GL::FLOAT, GL::TRUE, stride, OFF(normal));
	if (aTangent >= 0)
		GL::vertexAttribPointer(aTangent, 4, GL::FLOAT, GL::FALSE, stride, OFF(tangent));
	if (aBinorm >= 0)
		GL::vertexAttribPointer(aBinorm, 3, GL::FLOAT, GL::FALSE, stride, OFF(bitangent));

	#undef OFF
}

void GL::ObjModel::drawMesh(int index) const
{
	const Mesh & mesh = m_Meshes[index];
	GL::drawElements(GL::TRIANGLES, mesh.numIndices, GL::UNSIGNED_INT, (void *)(mesh.firstIndex * sizeof(Int)));
}
