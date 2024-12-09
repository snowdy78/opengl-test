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
        ShaderBuildSystem(const std::string &path_to_vertex_shader, const std::string &path_to_fragment_shader);
        void build();
        void draw() const;
    };

}
