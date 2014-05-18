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

#include "gl_model.h"
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
	class ObjModel : public Model
	{
	public:
		/**
		 * Constructor.
		 * @param resMgr Pointer to the resource manager.
		 * @param loader Resource loader to use.
		 * @param filename Name of the OBJ file to load.
		 */
		ObjModel(ResourceManager * resMgr, ::Resource::Loader & loader, const std::string & filename);

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

	private:
		unsigned m_HasNormals : 1;
		unsigned m_HasPositions : 1;
		unsigned m_HasTangents : 1;
		unsigned m_HasTexCoords : 1;

		ObjModel(const ObjModel &);
		ObjModel & operator=(const ObjModel &);
	};

	/** Strong pointer to the in-memory representation of an Alias|Wavefront OBJ model. */
	typedef std::shared_ptr<ObjModel> ObjModelPtr;
	/** Weak pointer to the in-memory representation of an Alias|Wavefront OBJ model. */
	typedef std::weak_ptr<ObjModel> ObjModelWeakPtr;
}

#endif
