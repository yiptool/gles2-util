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
#ifndef __9269eef9e4d4ea2da34fa05de87db468__
#define __9269eef9e4d4ea2da34fa05de87db468__

#include "gl_resource.h"
#include "gl_buffer.h"
#include "gl_texture.h"
#include "gl_attrib.h"
#include <yip-imports/resource_loader.h>
#include <yip-imports/gl.h>
#include <memory>

#ifdef HAVE_GLM
#include <yip-imports/glm/glm.hpp>
#endif

namespace GL
{
	/** An in-memory representation of a Alias|Wavefront OBJ model file. */
	class ObjModel : public Resource
	{
	public:
		/** Material. */
		struct Material
		{
		  #ifdef HAVE_GLM
			glm::vec4 ambient;					/**< Ambient reflectivity. */
			glm::vec4 diffuse;					/**< Diffuse reflectivity. */
			glm::vec4 specular;					/**< Specular reflectivity. */
		  #else
			Float ambient[4];					/**< Ambient reflectivity. */
			Float diffuse[4];					/**< Diffuse reflectivity. */
			Float specular[4];					/**< Specular reflectivity. */
		  #endif
			Float shininess;					/**< Shininess. */
			Float opacity;						/**< Opacity. */
			GL::TexturePtr texture;				/**< Texture. */
			GL::TexturePtr bumpMap;				/**< Bump map texture. */
		};

		/** Mesh. */
		struct Mesh
		{
			const Material * material;			/**< Pointer to the material. */
			Int firstIndex;						/**< First index. */
			Int numIndices;						/**< Number of indices. */
		};

		/**
		 * Constructor.
		 * @param resMgr Pointer to the resource manager.
		 * @param loader Resource loader to use.
		 * @param filename Name of the OBJ file to load.
		 */
		ObjModel(ResourceManager * resMgr, ::Resource::Loader & loader, const std::string & filename);

		/** Releases associated OpenGL resources. */
		void destroy() override;

		/**
		 * Returns number of materials.
		 * @return Number of materials.
		 */
		inline size_t numMaterials() const { return m_Materials.size(); }

		/**
		 * Returns reference to the specified material.
		 * @param index Index of the material.
		 * @return Reference to the specified material.
		 */
		inline const Material & material(size_t index) const { return m_Materials[index]; }

		/**
		 * Returns number of meshes.
		 * @return Number of meshes.
		 */
		inline size_t numMeshes() const { return m_Meshes.size(); }

		/**
		 * Returns reference to the specified mesh.
		 * @param index Index of the mesh.
		 * @return Reference to the specified mesh.
		 */
		inline const Mesh & mesh(size_t index) const { return m_Meshes[index]; }

		/**
		 * Retrieves the index buffer.
		 * @return Pointer to the index buffer.
		 */
		inline const GL::BufferPtr & indexBuffer() const noexcept { return m_Indices; }

		/**
		 * Retrieves vertex index buffer.
		 * @return Pointer to vertex index buffer.
		 */
		inline const GL::BufferPtr & vertexBuffer() const noexcept { return m_Vertices; }

		/**
		 * Retrieves X coordinate of a center of the model.
		 * @return X coordinate of a center of the model.
		 */
		inline float centerX() const noexcept { return m_Center[0]; }

		/**
		 * Retrieves Y coordinate of a center of the model.
		 * @return Y coordinate of a center of the model.
		 */
		inline float centerY() const noexcept { return m_Center[1]; }

		/**
		 * Retrieves Z coordinate of a center of the model.
		 * @return Z coordinate of a center of the model.
		 */
		inline float centerZ() const noexcept { return m_Center[2]; }

	  #ifdef HAVE_GLM
		/**
		 * Retrieves center of the model.
		 * @return Center of the model.
		 */
		inline const glm::vec3 & center() const noexcept { return m_Center; }
	  #endif

		/**
		 * Retrieves size of the model by the X axis.
		 * @return Size of the model by the X axis.
		 */
		inline float sizeX() const noexcept { return m_Size[0]; }

		/**
		 * Retrieves size of the model by the Y axis.
		 * @return Size of the model by the Y axis.
		 */
		inline float sizeY() const noexcept { return m_Size[1]; }

		/**
		 * Retrieves size of the model by the Z axis.
		 * @return Size of the model by the Z axis.
		 */
		inline float sizeZ() const noexcept { return m_Size[2]; }

	  #ifdef HAVE_GLM
		/**
		 * Retrieves size of the model.
		 * @return Size of the model.
		 */
		inline const glm::vec3 & size() const noexcept { return m_Size; }
	  #endif

		/**
		 * Retrieves radius of the model.
		 * @return Radius of the model.
		 */
		inline float radius() const noexcept { return m_Radius; }

		/**
		 * Retrieves total number of triangles in the model.
		 * @return Number of triangles in the model.
		 */
		inline int numTriangles() const noexcept { return m_NumTriangles; }

		/**
		 * Retrieves total number of vertices in the model.
		 * @return Number of vertices in the model.
		 */
		inline int numVertices() const noexcept { return m_NumVertices; }

		/**
		 * Checks whether this model has normals.
		 * @return *true* if model has normals, *false* otherwise.
		 */
		inline bool hasNormals() const noexcept { return m_HasNormals != 0; }

		/**
		 * Checks whether this model has positions.
		 * @return *true* if model has positions, *false* otherwise.
		 */
		inline bool hasPositions() const noexcept { return m_HasPositions != 0; }

		/**
		 * Checks whether this model has tangents.
		 * @return *true* if model has tangents, *false* otherwise.
		 */
		inline bool hasTangents() const noexcept { return m_HasTangents != 0; }

		/**
		 * Checks whether this model has texture coordinates.
		 * @return *true* if model has texture coordinates, *false* otherwise.
		 */
		inline bool hasTexCoords() const noexcept { return m_HasTexCoords != 0; }

		/**
		 * Configures vertex attribute for positions.
		 * @param aPos Index of the attribute for vertex positions (use -1 to skip).
		 * @param aTexCoord Index of the attribute for texture coordinates (use -1 to skip).
		 * @param aNorm Index of the attribute for normals (use -1 to skip).
		 * @param aTangent Index of the attribute for tangents (use -1 to skip).
		 * @param aBinorm Index of the attribute for binormals (use -1 to skip).
		 */
		void bindVertexBuffer(int aPos, int aTexCoord = -1, int aNorm = -1, int aTangent = -1, int aBinorm = -1) const;

		/**
		 * Configures vertex attribute for positions.
		 * @param aPos Attribute for vertex positions (use default-constructed value to skip).
		 * @param aTexCoord Attribute for texture coordinates (use default-constructed value to skip).
		 * @param aNorm Attribute for normals (use default-constructed value to skip).
		 * @param aTangent Attribute for tangents (use default-constructed value to skip).
		 * @param aBinorm Attribute for binormals (use default-constructed value to skip).
		 */
		inline void bindVertexBuffer(const GL::Attrib & aPos, const GL::Attrib & aTexCoord = GL::Attrib(),
			const GL::Attrib & aNorm = GL::Attrib(), const GL::Attrib & aTangent = GL::Attrib(),
			const GL::Attrib & aBinorm = GL::Attrib()) const
		{
			bindVertexBuffer(aPos.location(), aTexCoord.location(), aNorm.location(), aTangent.location(),
				aBinorm.location());
		}

		/**
		 * Calls GL::drawElements for vertices of the specified mesh.
		 * @param index Index of the mesh.
		 */
		void drawMesh(int index) const;

	private:
		std::vector<Mesh> m_Meshes;
		std::vector<Material> m_Materials;
		GL::BufferPtr m_Indices;
		GL::BufferPtr m_Vertices;
	  #ifdef HAVE_GLM
		glm::vec3 m_Center;
		glm::vec3 m_Size;
	  #else
		float m_Center[3];
		float m_Size[3];
	  #endif
		float m_Radius;
		int m_NumTriangles;
		int m_NumVertices;
		unsigned m_HasNormals : 1;
		unsigned m_HasPositions : 1;
		unsigned m_HasTangents : 1;
		unsigned m_HasTexCoords : 1;

		ObjModel(const ObjModel &);
		ObjModel & operator=(const ObjModel &);
	};

	/** Strong pointer to the OpenGL ES framebuffer. */
	typedef std::shared_ptr<ObjModel> ObjModelPtr;
	/** Weak pointer to the OpenGL ES framebuffer. */
	typedef std::weak_ptr<ObjModel> ObjModelWeakPtr;
}

#endif
