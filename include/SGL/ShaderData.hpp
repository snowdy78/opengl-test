#pragma once

#include "SGLdecl.hpp"
#include <string>
#include <map>

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
        inline static std::map<Type, int> retype = {
            {Vertex, GL_VERTEX_SHADER},
            {Fragment, GL_FRAGMENT_SHADER},
            {Geometry, GL_GEOMETRY_SHADER},
            {TessEvaluation, GL_TESS_EVALUATION_SHADER},
            {TessControl, GL_TESS_CONTROL_SHADER},
            {Compute, GL_COMPUTE_SHADER}
        };
    private:
        Type type;
        bool is_created = false;
        GLuint shader;

        GLuint &operator*();
        const GLuint &operator*() const;

        friend class ShaderProgram;
		std::string loadFromFile(const std::string &path);
		void create(const std::string &source_code);

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