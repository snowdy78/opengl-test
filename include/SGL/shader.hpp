#pragma once

#include "SGLdecl.hpp"
#include <cstring>
#include <string>

namespace sgl
{
    struct Shader
    {
        enum ShaderType
        {
            Vertex,
            Fragment
        };
    private:
        ShaderType type;
        char *code;
        GLuint shader;

        GLuint &operator*();
        const GLuint &operator*() const;

        friend class ShaderProgram;
    public:
		Shader(ShaderType type, const std::string &shader_code);
        ~Shader();


		Shader(const Shader &)			  = delete;
		Shader &operator=(const Shader &) = delete;
        ShaderType getType() const;
        void compile();
        void remove();
    };
}