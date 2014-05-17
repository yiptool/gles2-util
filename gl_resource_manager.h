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
#ifndef __bd60f34af632e5ad2a9b5bb6a5b67443__
#define __bd60f34af632e5ad2a9b5bb6a5b67443__

#include "gl_texture.h"
#include "gl_shader.h"
#include "gl_program.h"
#include "gl_buffer.h"
#include "gl_renderbuffer.h"
#include "gl_framebuffer.h"
#include "gl_obj_model.h"
#include <yip-imports/resource_loader.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

namespace GL
{
	/** @cond */
	namespace Internal
	{
		// Key for unordered_map of shaders
		typedef std::pair<Enum, std::string> ShaderMapKey;
		struct ShaderMapKeyHash {
			inline size_t operator()(const ShaderMapKey & value) const
				{ return std::hash<std::string>()(value.second); }
		};
	}
	/** @endcond */

	/**
	 * Convenient manager of OpenGL resources.
	 *
	 * It is highly recommended that you call collectGarbage() periodically (e.g. once per frame)
	 * so that resource manager could cleanup internal structures. Not calling this method will
	 * result in negligible memory leaks.
	 *
	 * In this implementation resource manager does not cache resources in any way. Resources are
	 * kept "alive" only while there is at least one ResourcePtr pointing to it.
	 *
	 * Custom caching could be implemented on top of this class by subclassing it.
	 */
	class ResourceManager
	{
	public:
		/**
		 * Constructor.
		 * @param loader Custom loader for resources (optional).
		 */
		ResourceManager(::Resource::Loader & loader = ::Resource::Loader::standard());

		/** Destructor. */
		virtual ~ResourceManager();

		/** Destroys all resources managed by the resource manager. */
		void destroyAllResources();

		/**
		 * Cleans up internal storage.
		 * In default implementation this method cleans up internal tables from expired weak pointers.
		 * This method could be overriden in child classes that implement caching of resources.
		 */
		virtual void collectGarbage();

		/**
		 * Creates new vertex or index buffer.
		 * @param name Name of the buffer (optional). This is the name that will be returned by
		 * GL::Resource::name().
		 * @return Pointer to the buffer.
		 */
		BufferPtr createBuffer(const std::string & name = m_DefaultBufferName);

		/**
		 * Creates new vertex buffer for a 2D quad.
		 * The created buffer contains 4 vertices (two `GL::FLOAT`s per vertex) and should be rendered using
		 * the GL::TRIANGLE_STRIP primitive.
		 * @param x1 X coordinate of the top left corner.
		 * @param y1 Y coordinate of the top left corner.
		 * @param x2 X coordinate of the bottom right corner.
		 * @param y2 Y coordinate of the bottom right corner.
		 * @param name Name of the buffer (optional). This is the name that will be returned by
		 * GL::Resource::name().
		 * @return Pointer to the buffer.
		 */
		BufferPtr createVertexBufferForQuad(float x1, float y1, float x2, float y2,
			const std::string & name = m_DefaultBufferName);

		/**
		 * Creates new vertex buffer for a 2D quad with texture coordinates.
		 * The created buffer contains 4 vertices (vertex consists of two `GL::FLOAT`s for position followed
		 * by two `GL::FLOAT`s for texture coordinate) and should be rendered using
		 * the GL::TRIANGLE_STRIP primitive.
		 * @param x1 X coordinate of the top left corner.
		 * @param y1 Y coordinate of the top left corner.
		 * @param x2 X coordinate of the bottom right corner.
		 * @param y2 Y coordinate of the bottom right corner.
		 * @param s1 S texture coordinate of the top left corner (optional).
		 * @param t1 T texture coordinate of the top left corner (optional).
		 * @param s2 S texture coordinate of the bottom right corner (optional).
		 * @param t2 T texture coordinate of the bottom right corner (optional).
		 * @param name Name of the buffer (optional). This is the name that will be returned by
		 * GL::Resource::name().
		 * @return Pointer to the buffer.
		 */
		BufferPtr createVertexBufferForTexturedQuad(float x1, float y1, float x2, float y2,
			float s1 = 0.0f, float t1 = 0.0f, float s2 = 1.0f, float t2 = 1.0f,
			const std::string & name = m_DefaultBufferName);

		/**
		 * Creates new framebuffer.
		 * @param name Name of the framebuffer (optional). This is the name that will be returned by
		 * GL::Resource::name().
		 * @return Pointer to the framebuffer.
		 */
		FramebufferPtr createFramebuffer(const std::string & name = m_DefaultFramebufferName);

		/**
		 * Creates new renderbuffer.
		 * @param name Name of the renderbuffer (optional). This is the name that will be returned by
		 * GL::Resource::name().
		 * @return Pointer to the renderbuffer.
		 */
		RenderbufferPtr createRenderbuffer(const std::string & name = m_DefaultRenderbufferName);

		/**
		 * Creates new texture.
		 * This method always creates a new texture, even if there is one with the same name in the resource
		 * manager. Created texture is not registered within a manager.
		 * @param name Name of the texture (optional). This is the name that will be returned by
		 * GL::Resource::name().
		 * @return Pointer to the texture.
		 */
		TexturePtr createTexture(const std::string & name = m_DefaultTextureName);

		/**
		 * Loads texture with the specified name.
		 * This method does not load a texture if it has already been loaded; in this case it returns
		 * the cached texture.
		 * @param name Name of the texture.
		 * @return Pointer to the texture.
		 */
		TexturePtr getTexture(const std::string & name);

		/**
		 * Creates new shader.
		 * This method always creates a new shader, even if there is one with the same name in the resource
		 * manager. Created shader is not registered within a manager.
		 * @param type Type of the shader. Could be GL::VERTEX_SHADER or GL::FRAGMENT_SHADER.
		 * @param name Name of the shader (optional). This is the name that will be returned by
		 * GL::Resource::name().
		 * @return Pointer to the shader.
		 */
		ShaderPtr createShader(Enum type, const std::string & name = m_DefaultShaderName);

		/**
		 * Loads shader with the specified name.
		 * This method does not load a shader if it has already been loaded; in this case it returns
		 * the cached shader.
		 * @param type Type of the shader. Could be GL::VERTEX_SHADER or GL::FRAGMENT_SHADER.
		 * @param name Name of the shader.
		 * @return Pointer to the shader.
		 */
		ShaderPtr getShader(Enum type, const std::string & name);

		/**
		 * Creates new program.
		 * This method always creates a new program, even if there is one with the same name in the resource
		 * manager. Created program is not registered within a manager.
		 * @param name Name of the program (optional). This is the name that will be returned by
		 * GL::Resource::name().
		 * @return Pointer to the program.
		 */
		ProgramPtr createProgram(const std::string & name = m_DefaultProgramName);

		/**
		 * Creates new program from two shaders.
		 * This method always creates a new program, even if there is one with the same name in the resource
		 * manager. Created program is not registered within a manager.
		 * @param vertex Name of the vertex shader. The shader will be loaded using the getShader method.
		 * @param fragment Name of the fragment shader. The shader will be loaded using the getShader method.
		 * @param name Name of the program (optional). This is the name that will be returned by
		 * GL::Resource::name().
		 * @return Pointer to the program.
		 */
		ProgramPtr createProgram(const std::string & vertex, const std::string & fragment,
			const std::string & name = m_DefaultProgramName);

		/**
		 * Loads program with the specified name.
		 * This method does not load a program if it has already been loaded; in this case it returns
		 * the cached program.
		 * @param name Name of the program.
		 * @return Pointer to the program.
		 */
		ProgramPtr getProgram(const std::string & name);

		/**
		 * Parses the Alias|Wavefront OBJ model.
		 * @param loader Resource loader to use.
		 * @param name Name of the file.
		 * @return Pointer to the model.
		 */
		ObjModelPtr createObjModel(::Resource::Loader & loader, const std::string & name);

		/**
		 * Loads the specified Alias|Wavefront OBJ model from resource.
		 * @param name Name of the file.
		 * @return Pointer to the model.
		 */
		ObjModelPtr getObjModel(const std::string & name);

	private:
		static const std::string m_DefaultTextureName;
		static const std::string m_DefaultShaderName;
		static const std::string m_DefaultProgramName;
		static const std::string m_DefaultBufferName;
		static const std::string m_DefaultRenderbufferName;
		static const std::string m_DefaultFramebufferName;

		::Resource::Loader * m_ResourceLoader;
		std::vector<ResourceWeakPtr> m_AllResources;
		std::unordered_map<std::string, TextureWeakPtr> m_Textures;
		std::unordered_map<Internal::ShaderMapKey, ShaderWeakPtr, Internal::ShaderMapKeyHash> m_Shaders;
		std::unordered_map<std::string, ProgramWeakPtr> m_Programs;
		std::unordered_map<std::string, ObjModelWeakPtr> m_ObjModels;

		template <class T> void collectGarbageIn(T & collection);
		template <class T, class P, class M, class K>
			std::shared_ptr<T> getResource(M & map, const K & key, bool * isNew);

		ResourceManager(const ResourceManager &) = delete;
		ResourceManager & operator=(const ResourceManager &) = delete;

		friend class Shader;
		friend class Program;
		friend class GLTexture;
	};

	/** Strong pointer to the resource manager. */
	typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;
}

#endif
