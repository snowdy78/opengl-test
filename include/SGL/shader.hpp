#pragma once

#include "SGLdecl.hpp"
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
        char *code = nullptr;
        GLuint shader;

        GLuint &operator*();
        const GLuint &operator*() const;

        friend class ShaderProgram;
		bool loadFromFile(const std::string &path);

	public:
		Shader();
		Shader(ShaderType type, const std::string &shader_code);
        ~Shader();

		void load(const std::string &path, ShaderType type);

		Shader(const Shader &)			  = delete;
		Shader &operator=(const Shader &) = delete;
        ShaderType getType() const;
        bool compile();
        void remove();
    };
}