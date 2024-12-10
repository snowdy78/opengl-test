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
            Fragment,
            Geometry,
            TessEvaluation,
            TessControl,
            Compute
        };
    private:
        Type type;
        bool is_created = false;
        GLuint shader;

        GLuint &operator*();
        const GLuint &operator*() const;

        friend class ShaderProgram;
		std::string loadFromFile(const std::string &path);

	public:
		ShaderData();
		ShaderData(Type type, const std::string &shader_code);
        ~ShaderData();

		bool load(const std::string &path, Type type);

		ShaderData(const ShaderData &)			  = delete;
		ShaderData &operator=(const ShaderData &) = delete;
        Type getType() const;
        bool compile();
        void remove();
    };
}