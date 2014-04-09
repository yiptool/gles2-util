
GLWrappers
==========

This is the convenient C++11 library for cross-platform OpenGL ES 2.0 programming.

Please note that OpenGL ES context creation and management is outside of the scope
of this library. This library only provides convenient wrappers for OpenGL ES API on
both the desktop and mobile platforms.

This README contains a quick tour over the features of the library. For complete
list of types, constants, functions and classes, please **build** the reference
manual using the [Doxygen](http://www.stack.nl/~dimitri/doxygen/) tool.


Compiling this library
----------------------

This library is not intended to be built directly. Instead it is supposed
to be included into projects using the [Yip](https://github.com/zapolnov/yip.git).

Use the `import gles2_wrappers` directive in your `Yipfile` to use this library.


Library overview
----------------

This library includes convenient C++ wrappers for OpenGL resources (textures,
shaders, etc.).

The *GL::Resource* class is a base class for all OpenGL resources. All managed
resources have names which could be obtained using the *name()* method
(usually resource name is a name of file from which resource has been loaded).

The *GL::ResourceManager* class is a manager of resources. It creates instances
of resources and tracks their usage.

### Resource loading

There are convenient methods available in the *GL::ResourceManager* class:

*getShader(type, name)*  
*getProgram(name)*  
*getTexture(name)*  

These methods load shaders, programs and textures respectively from files
with the specified *name* and store them in the resource manager. If resource
is already in memory, then these methods simply return a reference to the
same resource.

#### File format of shaders

Shaders are simply source files in the GLSL language.

Please note that you have to support both GLSL and ESSL (OpenGL ES dialect of
GLSL) in your shaders. For example, in OpenGL ES you have to specify floating-point
precision in the fragment shader. This is not supported in "desktop" OpenGL.

You could use the *GL_ES* preprocessor definition to distinguish ESSL from GLSL:

     #ifdef GL_ES
     precision mediump float;
     #endif

#### File format of programs

Programs are represented using a simple text format.

Each line of a program file is either an empty line, a directive or a shader source
code. Empty lines are ignored. Lines starting with the '%' symbol are considered
directives. Only two directives are allowed: *%vertex* and *%fragment*.

The *%vertex* directive starts source code of a vertex shader. The *%fragment*
directive starts source code of a fragment shader. Optionally you could specify a
file name for any of this directives. In this case shader will be loaded from
the specified file.

Sample program file:

     %vertex

     attribute vec2 a_position;
     void main()
     {
         gl_Position = a_position;
     }

     %fragment

     #ifdef GL_ES
     precision mediump float;
     #endif

     void main()
     {
         gl_FragColor = vec4(1.0f);
     }

Sample program file that loads shaders from another files:

     %vertex shader.vsh
     %fragment shader.fsh

Please note that shader file names are relative to the resources directory, not
to the directory where the program file is located.

#### Custom resource loader

Default behavior of the library is to load resources using the standard cross-platform
mechanism (for more information see the [resources](https://github.com/zapolnov/yip-resources)
for more information.  If this is not a desired behavior, custom resource loader could be
used. Overload the Resource::Loader class and pass it's instance to the GL::ResourceManager
constructor:

     class MyResourceLoader : public Resource::Loader
     {
         Resource::StreamPtr openResource(const std::string & name)
         {
             // ...
             return std::static_pointer_cast<std::istream>(std::make_shared<std::ifstream>(name));
         }
         std::string loadResource(const std::string & name)
         {
             // It is not necessary to overload this method: default implementation uses openResource()
         }
     };
     
     // ...
     
     static MyResourceLoader loader;
     GL::ResourceManager manager(loader);

Please note that GL::ResourceManager does not take ownership of the passed loader. It is
application responsibility to ensure that passed resource loader is alive for a whole
lifetime of the GL::ResourceManager instance.

### Dynamic resource creation

If you wouldn't like to load resource from file and would like to create it
dynamically, then the following methods are available:

*createShader(type, name)*  
*createProgram(name)*  
*createTexture(name)*  

Note that these methods do not register resource in the manager. This means
that *getShader*, *getProgram* and *getTexture* methods will not be able to
retrieve these resources by their names. The only place where the name you pass
to these methods is used, is the return value of the *name()* method of the
corresponding instance of *GL::Resource*.

### Resource tracking

For *GL::ResourceManager* to work properly you have to periodically call the
*collectGarbage()* method. If you decline to do so, negligible memory leaks
are possible.

Please note that resource manager does not implement any caching: resources are
considered alive only while there is at least one reference to them. If you want
to cache the resources, you have to subclass the *GL::ResourceManager* class and
implement caching functionality yourself.


License
=======

Copyright © 2014 Nikolay Zapolnov (zapolnov@gmail.com).

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
