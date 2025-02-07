#pragma once

#include "SGLdecl.hpp"
#include <string>

namespace sgl
{
    struct ShaderData
    {
        enum Type
        {
            Vertex, // DONT MAKE IT and etc. EQUAL TO GL_VERTEX_SHADER
            Fragment,
            Geometry,
            TessEvaluation,
            TessControl,
            Compute,
            Unknown = -1
        };
        enum BufferAllocationType
		{
			Static = GL_STATIC_DRAW,
			Dynamic = GL_DYNAMIC_DRAW,
            Stream = GL_STREAM_DRAW
		};
    private:
		BufferAllocationType buffer_type = Static;
        Type type = Unknown;
        GLuint shader = 0;

        friend class ShaderProgram;
		std::string loadFromFile(const std::string &path);
		void create(Type type, const std::string &source_code);
        static GLenum toShaderType(Type type);
        static GLenum toBufferAllocationType(BufferAllocationType type);
        
        public:
		ShaderData();
		ShaderData(Type type, const std::string &code_str);
        ~ShaderData();
        
		bool load(const std::string &path, Type type);
		ShaderData(const ShaderData &another_shader) = delete;
        ShaderData(ShaderData &&other);
        bool exist() const;
        GLuint getDescriptor() const; // TODO move to private
        BufferAllocationType getBufferAllocType() const;
        void setBufferAllocType(BufferAllocationType type);
        Type getType() const;
        bool compile();
        void remove();
    };
}