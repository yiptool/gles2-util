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
#ifndef __9754270c913262e56ca07abcc0bebc63__
#define __9754270c913262e56ca07abcc0bebc63__

#include <yip-imports/gl.h>
#include "gl_resource.h"

namespace GL
{
	class ResourceManager;

	/** OpenGL ES vertex or index buffer. */
	class Buffer : public Resource
	{
	public:
		/**
		 * Returns raw OpenGL ES handle of the buffer.
		 * @return Raw handle of the buffer.
		 */
		inline UInt handle() const { return m_Handle; }

		/**
		 * Binds buffer into the OpenGL context.
		 * This is equivalent to GL::bindBuffer.
		 * @param target Target to bind buffer to.
		 */
		inline void bind(Enum target) { GL::bindBuffer(target, m_Handle); }

	protected:
		/**
		 * Constructor.
		 * @param resMgr Pointer to the resource manager.
		 * @param resName Name of the buffer resource.
		 */
		Buffer(ResourceManager * resMgr, const std::string & resName);

		/** Destructor. */
		~Buffer();

		/**
		 * Releases the associated OpenGL buffer.
		 * This is equivalent to GL::deleteBuffers.
		 */
		void destroy() override;

	private:
		UInt m_Handle;
		ResourceManager * m_Manager;

		Buffer(const Buffer &) = delete;
		Buffer & operator=(const Buffer &) = delete;

		friend class ResourceManager;
	};

	/** Strong pointer to the OpenGL ES buffer. */
	typedef std::shared_ptr<Buffer> BufferPtr;
	/** Weak pointer to the OpenGL ES buffer. */
	typedef std::weak_ptr<Buffer> BufferWeakPtr;
}

#endif
