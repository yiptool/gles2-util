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
#ifndef __2be3f33524fee0b1578cc7a37eced312__
#define __2be3f33524fee0b1578cc7a37eced312__

#include "gl_program.h"
#include "gl_buffer.h"
#include <yip-imports/cxx-util/macros.h>
#include <yip-imports/gl.h>
#include <vector>
#include <string>

#ifdef HAVE_GLM
#include <yip-imports/glm/glm.hpp>
#endif

namespace GL
{
	/**
	 * Convenient C++ wrapper for shader attributes.
	 * This class caches location of the attribute.
	 */
	class Attrib
	{
	public:
		/** Constructor. */
		inline Attrib()
			: m_Location(-1)
		{
		}

		/**
		 * Constructor.
		 * @param program Pointer to the program.
		 * @param name Name of the attribute.
		 */
		inline Attrib(const GL::ProgramPtr & program, const std::string & name)
			: m_Program(program),
			  m_Name(name)
		{
			m_Location = program->getAttribLocation(name);
		}

		/** Destructor. */
		inline ~Attrib() {}

		/**
		 * Retrieves pointer to the program.
		 * @return program Pointer to the program.
		 */
		inline const GL::ProgramPtr & program() const
		{
			return m_Program;
		}

		/**
		 * Retrieves name of the attribute.
		 * @return name of the attribute.
		 */
		inline const std::string & name() const
		{
			return m_Name;
		}

		/**
		 * Retrieves location of the attribute.
		 * @return Location of the attribute.
		 */
		inline int location() const
		{
			return m_Location;
		}

		/**
		 * Sets value for the `float` attribute.
		 * @param value Value.
		 */
		inline void set1f(Float value)
		{
			if (LIKELY(m_Location >= 0))
				GL::vertexAttrib1f(m_Location, value);
		}

		/**
		 * Sets value for the `vec2` attribute.
		 * @param x Value for the first component.
		 * @param y Value for the second component.
		 */
		inline void set2f(Float x, Float y)
		{
			if (LIKELY(m_Location >= 0))
				GL::vertexAttrib2f(m_Location, x, y);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `vec2` attribute.
		 * @param value Value.
		 */
		inline void set2f(const glm::vec2 & value)
		{
			STATIC_ASSERT(sizeof(value.x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::vertexAttrib2fv(m_Location, &value[0]);
		}
	  #endif

		/**
		 * Sets value for the `vec3` attribute.
		 * @param x Value for the first component.
		 * @param y Value for the second component.
		 * @param z Value for the third component.
		 */
		inline void set3f(Float x, Float y, Float z)
		{
			if (LIKELY(m_Location >= 0))
				GL::vertexAttrib3f(m_Location, x, y, z);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `vec3` attribute.
		 * @param value Value.
		 */
		inline void set3f(const glm::vec3 & value)
		{
			STATIC_ASSERT(sizeof(value.x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::vertexAttrib3fv(m_Location, &value[0]);
		}
	  #endif

		/**
		 * Sets value for the `vec4` attribute.
		 * @param x Value for the first component.
		 * @param y Value for the second component.
		 * @param z Value for the third component.
		 * @param w Value for the fourth component.
		 */
		inline void set4f(Float x, Float y, Float z, Float w)
		{
			if (LIKELY(m_Location >= 0))
				GL::vertexAttrib4f(m_Location, x, y, z, w);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `vec4` attribute.
		 * @param value Value.
		 */
		inline void set4f(const glm::vec4 & value)
		{
			STATIC_ASSERT(sizeof(value.x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::vertexAttrib4fv(m_Location, &value[0]);
		}

		/**
		 * Sets value for the `vec4` attribute.
		 * @param value Value.
		 */
		inline void set4f(const glm::quat & value)
		{
			STATIC_ASSERT(sizeof(value.x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::vertexAttrib4fv(m_Location, &value[0]);
		}
	  #endif

		/**
		 * Sets vertex buffer as the data source for the attribute.
		 * @note This method changes buffer bound to the *GL::ARRAY_BUFFER* target.
		 * @param size Number of components.
		 * @param type Data type of component.
		 * @param norm Set to *GL::TRUE* if values should be normalized.
		 * @param stride Stride.
		 * @param buffer Vertex buffer.
		 * @param offset Offset from the beginning of the buffer, in bytes.
		 */
		inline void useBuffer(Int size, Enum type, Boolean norm, Sizei stride,
			const GL::BufferPtr & buffer, size_t offset)
		{
			buffer->bind(GL::ARRAY_BUFFER);
			GL::vertexAttribPointer(m_Location, size, type, norm, stride, (void *)offset);
		}

	private:
		GL::ProgramPtr m_Program;
		std::string m_Name;
		int m_Location;
	};
}

#endif
