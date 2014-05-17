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
#ifndef __d484ad4f1be33d6d1728f43ef086ead4__
#define __d484ad4f1be33d6d1728f43ef086ead4__

#include "gl_program.h"
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
	 * Convenient C++ wrapper for uniform shader variables.
	 * This class caches location of the uniform.
	 */
	class Uniform
	{
	public:
		/** Constructor. */
		inline Uniform()
			: m_Location(-1)
		{
		}

		/**
		 * Constructor.
		 * @param program Pointer to the program.
		 * @param name Name of the uniform.
		 */
		inline Uniform(const GL::ProgramPtr & program, const std::string & name)
			: m_Program(program),
			  m_Name(name)
		{
			m_Location = program->getUniformLocation(name);
		}

		/** Destructor. */
		inline ~Uniform() {}

		/**
		 * Retrieves pointer to the program.
		 * @return program Pointer to the program.
		 */
		inline const GL::ProgramPtr & program() const
		{
			return m_Program;
		}

		/**
		 * Retrieves name of the uniform.
		 * @return name of the uniform.
		 */
		inline const std::string & name() const
		{
			return m_Name;
		}

		/**
		 * Retrieves location of the uniform.
		 * @return Location of the uniform.
		 */
		inline int location() const
		{
			return m_Location;
		}

		/**
		 * Sets value for the `float` uniform.
		 * @param value Value.
		 */
		inline void set1f(Float value)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform1f(m_Location, value);
		}

		/**
		 * Sets value for the `float[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set1fv(const Float * values, Sizei length)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform1fv(m_Location, length, values);
		}

		/**
		 * Sets value for the `float[]` uniform.
		 * @param values Array of values.
		 */
		inline void set1fv(const std::vector<Float> & values)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform1fv(m_Location, Sizei(values.size()), values.data());
		}

		/**
		 * Sets value for the `int` uniform.
		 * @param value Value.
		 */
		inline void set1i(Int value)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform1i(m_Location, value);
		}

		/**
		 * Sets value for the `int[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set1iv(const Int * values, Sizei length)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform1iv(m_Location, length, values);
		}

		/**
		 * Sets value for the `int[]` uniform.
		 * @param values Array of values.
		 */
		inline void set1iv(const std::vector<Int> & values)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform1iv(m_Location, Sizei(values.size()), values.data());
		}

		/**
		 * Sets value for the `vec2` uniform.
		 * @param x Value for the first component.
		 * @param y Value for the second component.
		 */
		inline void set2f(Float x, Float y)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform2f(m_Location, x, y);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `vec2` uniform.
		 * @param value Value.
		 */
		inline void set2f(const glm::vec2 & value)
		{
			STATIC_ASSERT(sizeof(value.x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniform2fv(m_Location, 1, &value[0]);
		}
	  #endif

		/**
		 * Sets value for the `vec2[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set2fv(const Float * values, Sizei length)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform2fv(m_Location, length, values);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `vec2[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set2fv(const glm::vec2 * values, Sizei length)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniform2fv(m_Location, length, &values[0][0]);
		}
	  #endif

		/**
		 * Sets value for the `vec2[]` uniform.
		 * @param values Array of values.
		 */
		inline void set2fv(const std::vector<Float> & values)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform2fv(m_Location, Sizei(values.size() / 2), values.data());
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `vec2[]` uniform.
		 * @param values Array of values.
		 */
		inline void set2fv(const std::vector<glm::vec2> & values)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniform2fv(m_Location, Sizei(values.size()), &values[0][0]);
		}
	  #endif

		/**
		 * Sets value for the `ivec2` uniform.
		 * @param x Value for the first component.
		 * @param y Value for the second component.
		 */
		inline void set2i(Int x, Int y)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform2i(m_Location, x, y);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `ivec2` uniform.
		 * @param value Value.
		 */
		inline void set2i(const glm::ivec2 & value)
		{
			STATIC_ASSERT(sizeof(value.x) == sizeof(Int));
			if (LIKELY(m_Location >= 0))
				GL::uniform2iv(m_Location, 1, &value[0]);
		}
	  #endif

		/**
		 * Sets value for the `ivec2[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set2iv(const Int * values, Sizei length)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform2iv(m_Location, length, values);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `ivec2[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set2iv(const glm::ivec2 * values, Sizei length)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Int));
			if (LIKELY(m_Location >= 0))
				GL::uniform2iv(m_Location, length, &values[0][0]);
		}
	  #endif

		/**
		 * Sets value for the `ivec2[]` uniform.
		 * @param values Array of values.
		 */
		inline void set2iv(const std::vector<Int> & values)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform2iv(m_Location, Sizei(values.size() / 2), values.data());
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `ivec2[]` uniform.
		 * @param values Array of values.
		 */
		inline void set2iv(const std::vector<glm::ivec2> & values)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Int));
			if (LIKELY(m_Location >= 0))
				GL::uniform2iv(m_Location, Sizei(values.size()), &values[0][0]);
		}
	  #endif

		/**
		 * Sets value for the `vec3` uniform.
		 * @param x Value for the first component.
		 * @param y Value for the second component.
		 * @param z Value for the third component.
		 */
		inline void set3f(Float x, Float y, Float z)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform3f(m_Location, x, y, z);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `vec3` uniform.
		 * @param value Value.
		 */
		inline void set3f(const glm::vec3 & value)
		{
			STATIC_ASSERT(sizeof(value.x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniform3fv(m_Location, 1, &value[0]);
		}
	  #endif

		/**
		 * Sets value for the `vec3[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set3fv(const Float * values, Sizei length)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform3fv(m_Location, length, values);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `vec3[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set3fv(const glm::vec3 * values, Sizei length)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniform3fv(m_Location, length, &values[0][0]);
		}
	  #endif

		/**
		 * Sets value for the `vec3[]` uniform.
		 * @param values Array of values.
		 */
		inline void set3fv(const std::vector<Float> & values)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform3fv(m_Location, Sizei(values.size() / 3), values.data());
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `vec3[]` uniform.
		 * @param values Array of values.
		 */
		inline void set3fv(const std::vector<glm::vec3> & values)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniform3fv(m_Location, Sizei(values.size()), &values[0][0]);
		}
	  #endif

		/**
		 * Sets value for the `ivec3` uniform.
		 * @param x Value for the first component.
		 * @param y Value for the second component.
		 * @param z Value for the third component.
		 */
		inline void set3i(Int x, Int y, Int z)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform3i(m_Location, x, y, z);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `ivec3` uniform.
		 * @param value Value.
		 */
		inline void set3i(const glm::ivec3 & value)
		{
			STATIC_ASSERT(sizeof(value.x) == sizeof(Int));
			if (LIKELY(m_Location >= 0))
				GL::uniform3iv(m_Location, 1, &value[0]);
		}
	  #endif

		/**
		 * Sets value for the `ivec3[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set3iv(const Int * values, Sizei length)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform3iv(m_Location, length, values);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `ivec3[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set3iv(const glm::ivec3 * values, Sizei length)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Int));
			if (LIKELY(m_Location >= 0))
				GL::uniform3iv(m_Location, length, &values[0][0]);
		}
	  #endif

		/**
		 * Sets value for the `ivec3[]` uniform.
		 * @param values Array of values.
		 */
		inline void set3iv(const std::vector<Int> & values)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform3iv(m_Location, Sizei(values.size() / 3), values.data());
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `ivec3[]` uniform.
		 * @param values Array of values.
		 */
		inline void set3iv(const std::vector<glm::ivec3> & values)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Int));
			if (LIKELY(m_Location >= 0))
				GL::uniform3iv(m_Location, Sizei(values.size()), &values[0][0]);
		}
	  #endif

		/**
		 * Sets value for the `vec4` uniform.
		 * @param x Value for the first component.
		 * @param y Value for the second component.
		 * @param z Value for the third component.
		 * @param w Value for the fourth component.
		 */
		inline void set4f(Float x, Float y, Float z, Float w)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform4f(m_Location, x, y, z, w);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `vec4` uniform.
		 * @param value Value.
		 */
		inline void set4f(const glm::vec4 & value)
		{
			STATIC_ASSERT(sizeof(value.x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniform4fv(m_Location, 1, &value[0]);
		}

		/**
		 * Sets value for the `vec4` uniform.
		 * @param value Value.
		 */
		inline void set4f(const glm::quat & value)
		{
			STATIC_ASSERT(sizeof(value.x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniform4fv(m_Location, 1, &value[0]);
		}
	  #endif

		/**
		 * Sets value for the `vec4[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set4fv(const Float * values, Sizei length)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform4fv(m_Location, length, values);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `vec4[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set4fv(const glm::vec4 * values, Sizei length)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniform4fv(m_Location, length, &values[0][0]);
		}

		/**
		 * Sets value for the `vec4[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set4fv(const glm::quat * values, Sizei length)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniform4fv(m_Location, length, &values[0][0]);
		}
	  #endif

		/**
		 * Sets value for the `vec4[]` uniform.
		 * @param values Array of values.
		 */
		inline void set4fv(const std::vector<Float> & values)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform4fv(m_Location, Sizei(values.size() / 4), values.data());
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `vec4[]` uniform.
		 * @param values Array of values.
		 */
		inline void set4fv(const std::vector<glm::vec4> & values)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniform4fv(m_Location, Sizei(values.size()), &values[0][0]);
		}

		/**
		 * Sets value for the `vec4[]` uniform.
		 * @param values Array of values.
		 */
		inline void set4fv(const std::vector<glm::quat> & values)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniform4fv(m_Location, Sizei(values.size()), &values[0][0]);
		}
	  #endif

		/**
		 * Sets value for the `ivec4` uniform.
		 * @param x Value for the first component.
		 * @param y Value for the second component.
		 * @param z Value for the third component.
		 * @param w Value for the fourth component.
		 */
		inline void set4i(Int x, Int y, Int z, Int w)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform4i(m_Location, x, y, z, w);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `ivec4` uniform.
		 * @param value Value.
		 */
		inline void set4i(const glm::ivec4 & value)
		{
			STATIC_ASSERT(sizeof(value.x) == sizeof(Int));
			if (LIKELY(m_Location >= 0))
				GL::uniform4iv(m_Location, 1, &value[0]);
		}
	  #endif

		/**
		 * Sets value for the `ivec4[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set4iv(const Int * values, Sizei length)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform4iv(m_Location, length, values);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `ivec4[]` uniform.
		 * @param values Pointer to the array of values.
		 * @param length Size of the array.
		 */
		inline void set4iv(const glm::ivec4 * values, Sizei length)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Int));
			if (LIKELY(m_Location >= 0))
				GL::uniform4iv(m_Location, length, &values[0][0]);
		}
	  #endif

		/**
		 * Sets value for the `ivec4[]` uniform.
		 * @param values Array of values.
		 */
		inline void set4iv(const std::vector<Int> & values)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniform4iv(m_Location, Sizei(values.size() / 4), values.data());
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `ivec4[]` uniform.
		 * @param values Array of values.
		 */
		inline void set4iv(const std::vector<glm::ivec4> & values)
		{
			STATIC_ASSERT(sizeof(values[0].x) == sizeof(Int));
			if (LIKELY(m_Location >= 0))
				GL::uniform4iv(m_Location, Sizei(values.size()), &values[0][0]);
		}
	  #endif

		/**
		 * Sets value for the `mat2` or `mat2[]` uniform.
		 * @param values Array of values.
		 * @param count Number of matrices.
		 */
		inline void setMatrix2fv(const Float * values, Sizei count = 1)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix2fv(m_Location, count, GL::FALSE, values);
		}

		/**
		 * Sets value for the `mat2` or `mat2[]` uniform.
		 * This method transposes the matrix before assigning it to the uniform.
		 * @param values Array of values.
		 * @param count Number of matrices.
		 */
		inline void setTransposedMatrix2fv(const Float * values, Sizei count = 1)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix2fv(m_Location, count, GL::TRUE, values);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `mat2` uniform.
		 * @param value Reference to the matrix.
		 */
		inline void setMatrix2fv(const glm::mat2 & value)
		{
			STATIC_ASSERT(sizeof(value[0][0]) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix2fv(m_Location, 1, GL::FALSE, &value[0][0]);
		}

		/**
		 * Sets value for the `mat2[]` uniform.
		 * @param values Pointer to the array of matrices.
		 * @param count Number of matrices.
		 */
		inline void setMatrix2fv(const glm::mat2 * values, Sizei count = 1)
		{
			STATIC_ASSERT(sizeof(values[0][0][0]) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix2fv(m_Location, count, GL::FALSE, &values[0][0][0]);
		}

		/**
		 * Sets value for the `mat2[]` uniform.
		 * @param values Array of matrices.
		 */
		inline void setMatrix2fv(const std::vector<glm::mat2> & values)
		{
			STATIC_ASSERT(sizeof(values[0][0][0]) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix2fv(m_Location, Sizei(values.size()), GL::FALSE, &values[0][0][0]);
		}
	  #endif

		/**
		 * Sets value for the `mat3` or `mat3[]` uniform.
		 * @param values Array of values.
		 * @param count Number of matrices.
		 */
		inline void setMatrix3fv(const Float * values, Sizei count = 1)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix3fv(m_Location, count, GL::FALSE, values);
		}

		/**
		 * Sets value for the `mat3` or `mat3[]` uniform.
		 * This method transposes the matrix before assigning it to the uniform.
		 * @param values Array of values.
		 * @param count Number of matrices.
		 */
		inline void setTransposedMatrix3fv(const Float * values, Sizei count = 1)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix3fv(m_Location, count, GL::TRUE, values);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `mat3` uniform.
		 * @param value Reference to the matrix.
		 */
		inline void setMatrix3fv(const glm::mat3 & value)
		{
			STATIC_ASSERT(sizeof(value[0][0]) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix3fv(m_Location, 1, GL::FALSE, &value[0][0]);
		}

		/**
		 * Sets value for the `mat3[]` uniform.
		 * @param values Pointer to the array of matrices.
		 * @param count Number of matrices.
		 */
		inline void setMatrix3fv(const glm::mat3 * values, Sizei count = 1)
		{
			STATIC_ASSERT(sizeof(values[0][0][0]) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix3fv(m_Location, count, GL::FALSE, &values[0][0][0]);
		}

		/**
		 * Sets value for the `mat3[]` uniform.
		 * @param values Array of matrices.
		 */
		inline void setMatrix3fv(const std::vector<glm::mat3> & values)
		{
			STATIC_ASSERT(sizeof(values[0][0][0]) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix3fv(m_Location, Sizei(values.size()), GL::FALSE, &values[0][0][0]);
		}
	  #endif

		/**
		 * Sets value for the `mat4` or `mat4[]` uniform.
		 * @param values Array of values.
		 * @param count Number of matrices.
		 */
		inline void setMatrix4fv(const Float * values, Sizei count = 1)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix4fv(m_Location, count, GL::FALSE, values);
		}

		/**
		 * Sets value for the `mat4` or `mat4[]` uniform.
		 * This method transposes the matrix before assigning it to the uniform.
		 * @param values Array of values.
		 * @param count Number of matrices.
		 */
		inline void setTransposedMatrix4fv(const Float * values, Sizei count = 1)
		{
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix4fv(m_Location, count, GL::TRUE, values);
		}

	  #ifdef HAVE_GLM
		/**
		 * Sets value for the `mat4` uniform.
		 * @param value Reference to the matrix.
		 */
		inline void setMatrix4fv(const glm::mat4 & value)
		{
			STATIC_ASSERT(sizeof(value[0][0]) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix4fv(m_Location, 1, GL::FALSE, &value[0][0]);
		}

		/**
		 * Sets value for the `mat4[]` uniform.
		 * @param values Pointer to the array of matrices.
		 * @param count Number of matrices.
		 */
		inline void setMatrix4fv(const glm::mat4 * values, Sizei count = 1)
		{
			STATIC_ASSERT(sizeof(values[0][0][0]) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix4fv(m_Location, count, GL::FALSE, &values[0][0][0]);
		}

		/**
		 * Sets value for the `mat4[]` uniform.
		 * @param values Array of matrices.
		 */
		inline void setMatrix4fv(const std::vector<glm::mat4> & values)
		{
			STATIC_ASSERT(sizeof(values[0][0][0]) == sizeof(Float));
			if (LIKELY(m_Location >= 0))
				GL::uniformMatrix4fv(m_Location, Sizei(values.size()), GL::FALSE, &values[0][0][0]);
		}
	  #endif

	private:
		GL::ProgramPtr m_Program;
		std::string m_Name;
		int m_Location;
	};
}

#endif
