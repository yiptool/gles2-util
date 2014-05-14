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
#ifndef __8a35ec321935a1160dc5eddc005d8b9e__
#define __8a35ec321935a1160dc5eddc005d8b9e__

#include "gl_framebuffer.h"
#include <yip-imports/gl.h>

namespace GL
{
	/**
	 * RAII-style class for framebuffer binding.
	 * This class allows convenient and exception-safe binding and unbinding of framebuffers.
	 *
	 * It is recommended to create an instance of this class instead of calling GL::bindFramebuffer.
	 * @code
	 * GL::FramebufferBinder framebufferBinder(fb);
	 * // ...
	 * @endcode
	 */
	class FramebufferBinder
	{
	public:
		/**
		 * Constructor.
		 * Calls GL::bindFramebuffer with the specified framebuffer.
		 * @param fb Framebuffer to use.
		 * @param target Framebuffer binding target (default is GL::FRAMEBUFFER).
		 * @see GL::bindFramebuffer.
		 */
		inline FramebufferBinder(const GL::FramebufferPtr & fb, GL::Enum target = GL::FRAMEBUFFER)
			: m_Target(target),
			  m_PreviouslyBoundBuffer(0)
		{
			GL::getIntegerv(GL::FRAMEBUFFER_BINDING, &m_PreviouslyBoundBuffer);
			fb->bind(target);
		}

		/** Destructor. Calls GL::bindFramebuffer with framebuffer handle set to zero. */
		inline ~FramebufferBinder()
		{
			GL::bindFramebuffer(m_Target, m_PreviouslyBoundBuffer);
		}

	private:
		GL::Enum m_Target;
		GL::Int m_PreviouslyBoundBuffer;

		FramebufferBinder(const FramebufferBinder &) = delete;
		FramebufferBinder & operator=(const FramebufferBinder &) = delete;
	};
}

#endif
