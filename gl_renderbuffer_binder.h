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
#ifndef __65dc9912b9dedc0c1e0526c5b222e276__
#define __65dc9912b9dedc0c1e0526c5b222e276__

#include "gl_renderbuffer.h"
#include <yip-imports/gl.h>

namespace GL
{
	/**
	 * RAII-style class for renderbuffer binding.
	 * This class allows convenient and exception-safe binding and unbinding of renderbuffers.
	 *
	 * It is recommended to create an instance of this class instead of calling GL::bindRenderbuffer.
	 * @code
	 * GL::RenderbufferBinder renderbufferBinder(rb);
	 * // ...
	 * @endcode
	 */
	class RenderbufferBinder
	{
	public:
		/**
		 * Constructor.
		 * Calls GL::bindRenderbuffer with the specified renderbuffer.
		 * @param rb Renderbuffer to use.
		 * @param target Renderbuffer binding target (default is GL::RENDERBUFFER).
		 * @see GL::bindRenderbuffer.
		 */
		inline RenderbufferBinder(const GL::RenderbufferPtr & rb, GL::Enum target = GL::RENDERBUFFER)
			: m_Target(target)
		{
			rb->bind(target);
		}

		/** Destructor. Calls GL::bindRenderbuffer with renderbuffer handle set to zero. */
		inline ~RenderbufferBinder()
		{
			GL::bindRenderbuffer(m_Target, 0);
		}

	private:
		GL::Enum m_Target;

		RenderbufferBinder(const RenderbufferBinder &) = delete;
		RenderbufferBinder & operator=(const RenderbufferBinder &) = delete;
	};
}

#endif
