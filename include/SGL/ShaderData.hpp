#pragma once

#include "SGLdecl.hpp"
#include <string>

namespace sgl
{
    struct ShaderData
    {
        enum Type
        {
            Vertex,
            Fragment
        };
    private:
        Type type;
        char *code = nullptr;
        GLuint shader;

        GLuint &operator*();
        const GLuint &operator*() const;

        friend class ShaderProgram;
		bool loadFromFile(const std::string &path);

	public:
		ShaderData();
		ShaderData(Type type, const std::string &shader_code);
        ~ShaderData();

		void load(const std::string &path, Type type);

		ShaderData(const ShaderData &)			  = delete;
		ShaderData &operator=(const ShaderData &) = delete;
        Type getType() const;
        bool compile();
        void remove();
    };
}