#pragma once

#include "SGLdecl.hpp"
#include <string>
#include "Shader.hpp"
#include "ShaderProgram.hpp"

namespace sgl
{
    

    class ShaderBuildSystem : public ShaderProgram
    {
        Shader vertex_shader;
        Shader fragment_shader;

    public:
        ShaderBuildSystem(const std::string &vertex_shader_code, const std::string &fragment_shader_code);
        void build();
        void draw();
    };

}
