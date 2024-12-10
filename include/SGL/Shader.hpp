#pragma once

#include "SGLdecl.hpp"
#include <string>

#include "ShaderData.hpp"
#include "ShaderProgram.hpp"
#include "Component.hpp"

namespace sgl
{
    class Shader : public ShaderProgram, public Component
    {
        ShaderData vertex_shader;
        ShaderData fragment_shader;

    public:
        using Component::transform;
        Shader(const std::string &path_to_vertex_shader, const std::string &path_to_fragment_shader);
        void build();
        void draw() const override;
    };

}
