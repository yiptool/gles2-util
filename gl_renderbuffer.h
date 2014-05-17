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
#ifndef __a80ffac539eb132e65f6bab18d306a1b__
#define __a80ffac539eb132e65f6bab18d306a1b__

#include <yip-imports/gl.h>
#include "gl_resource.h"

namespace GL
{
	class ResourceManager;

	/** OpenGL ES renderbuffer. */
	class Renderbuffer : public Resource
	{
	public:
		/**
		 * Returns raw OpenGL ES handle of the renderbuffer.
		 * @return Raw handle of the renderbuffer.
		 */
		inline UInt handle() const { return m_Handle; }

		/**
		 * Binds renderbuffer into the OpenGL context.
		 * This is equivalent to GL::bindRenderbuffer.
		 * @param target Target to bind renderbuffer to (default is GL::RENDERBUFFER).
		 */
		inline void bind(Enum target = GL::RENDERBUFFER) { GL::bindRenderbuffer(target, m_Handle); }

	protected:
		/**
		 * Constructor.
		 * @param resMgr Pointer to the resource manager.
		 * @param resName Name of the renderbuffer resource.
		 */
		Renderbuffer(ResourceManager * resMgr, const std::string & resName);

		/** Destructor. */
		~Renderbuffer();

		/**
		 * Releases the associated OpenGL renderbuffer.
		 * This is equivalent to GL::deleteRenderbuffers.
		 */
		void destroy() override;

	private:
		UInt m_Handle;

		Renderbuffer(const Renderbuffer &) = delete;
		Renderbuffer & operator=(const Renderbuffer &) = delete;

		friend class ResourceManager;
	};

	/** Strong pointer to the OpenGL ES renderbuffer. */
	typedef std::shared_ptr<Renderbuffer> RenderbufferPtr;
	/** Weak pointer to the OpenGL ES renderbuffer. */
	typedef std::weak_ptr<Renderbuffer> RenderbufferWeakPtr;
}

#endif
