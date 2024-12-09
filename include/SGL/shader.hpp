#pragma once

#include "SGLdecl.hpp"
#include <string>

#include "Drawable.hpp"
#include "ShaderData.hpp"
#include "ShaderProgram.hpp"

namespace sgl
{
    class Shader : public ShaderProgram, public Drawable
    {
        ShaderData vertex_shader;
        ShaderData fragment_shader;

    public:
        Shader(const std::string &path_to_vertex_shader, const std::string &path_to_fragment_shader);
        void build();
        void draw() const override;
    };

}
