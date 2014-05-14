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
#ifndef __7a891cc7f4bf3fed8b291823644da539__
#define __7a891cc7f4bf3fed8b291823644da539__

#include "gl_buffer.h"
#include <yip-imports/gl.h>

namespace GL
{
	/**
	 * RAII-style class for vertex or index buffer binding.
	 * This class allows convenient and exception-safe binding and unbinding of buffers.
	 *
	 * It is recommended to create an instance of this class instead of calling GL::bindBuffer.
	 * @code
	 * GL::BufferBinder bufferBinder(fb);
	 * // ...
	 * @endcode
	 */
	class BufferBinder
	{
	public:
		/**
		 * Constructor.
		 * Calls GL::bindBuffer with the specified target and buffer.
		 * @param buf Buffer to use.
		 * @param target Buffer binding target.
		 * @see GL::bindBuffer.
		 */
		inline BufferBinder(const GL::BufferPtr & buf, GL::Enum target)
			: m_Target(target)
		{
			buf->bind(target);
		}

		/** Destructor. Calls GL::bindBuffer with buffer handle set to zero. */
		inline ~BufferBinder()
		{
			GL::bindBuffer(m_Target, 0);
		}

	private:
		GL::Enum m_Target;

		BufferBinder(const BufferBinder &) = delete;
		BufferBinder & operator=(const BufferBinder &) = delete;
	};
}

#endif
