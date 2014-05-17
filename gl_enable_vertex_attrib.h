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
#ifndef __2b2c926004582f6f844eb645ea663268__
#define __2b2c926004582f6f844eb645ea663268__

#include <yip-imports/gl.h>
#include "gl_attrib.h"

namespace GL
{
	/**
	 * RAII-style class for GL::enableVertexAttribArray and GL::disableVertexAttribArray.
	 * This class allows convenient and exception-safe use of vertex attrib arrays.
	 *
	 * It is recommended to create an instance of this class instead of calling
	 * GL::enableVertexAttribArray and GL::disableVertexAttribArray:
	 * @code
	 * GL::EnableVertexAttrib enable(verticesIndex);
	 * GL::drawArrays(GL::TRIANGLE_STRIP, 0, 4);
	 * @endcode
	 */
	class EnableVertexAttrib
	{
	public:
		/**
		 * Constructor.
		 * Calls GL::enableVertexAttribArray.
		 * @param index Index of the generic vertex attribute to be enabled.
		 * @see GL::enableVertexAttribArray, GL::disableVertexAttribArray.
		 */
		inline EnableVertexAttrib(UInt index)
			: m_Index(index)
		{
			enableVertexAttribArray(m_Index);
		}

		/**
		 * Constructor.
		 * Calls GL::enableVertexAttribArray.
		 * @param index Attribute to be enabled.
		 * @see GL::enableVertexAttribArray, GL::disableVertexAttribArray.
		 */
		inline EnableVertexAttrib(const GL::Attrib & index)
			: m_Index(index.location())
		{
			enableVertexAttribArray(m_Index);
		}

		/** Destructor. Calls GL::disableVertexAttribArray. */
		inline ~EnableVertexAttrib()
		{
			disableVertexAttribArray(m_Index);
		}

	private:
		GL::UInt m_Index;

		EnableVertexAttrib(const EnableVertexAttrib &) = delete;
		EnableVertexAttrib & operator=(const EnableVertexAttrib &) = delete;
	};
}

#endif
