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
#ifndef __d12b2aee2f614f99a2fc31a8f1149393__
#define __d12b2aee2f614f99a2fc31a8f1149393__

#include "gl_model.h"
#include <memory>

namespace GL
{
	/** A 3D model of the cube. */
	class CubeModel : public Model
	{
	public:
		/**
		 * Constructor.
		 * @param resMgr Pointer to the resource manager.
		 * @param size Dimensions of the cube.
		 * @param inside Set to *true* to make normals look inside the cube or to *false* to make them
		 * look outside.
		 * @param resName Name of the resource.
		 */
		CubeModel(ResourceManager * resMgr, float size, bool inside, const std::string & resName);

	private:
		CubeModel(const CubeModel &);
		CubeModel & operator=(const CubeModel &);
	};

	/** Strong pointer to the in-memory representation of an Alias|Wavefront OBJ model. */
	typedef std::shared_ptr<CubeModel> CubeModelPtr;
	/** Weak pointer to the in-memory representation of an Alias|Wavefront OBJ model. */
	typedef std::weak_ptr<CubeModel> CubeModelWeakPtr;
}

#endif
