#pragma once

#include "SGLdecl.hpp"
#include <string>
#include <cstring>
#include <vector>
#include <iostream>

namespace sgl
{
    struct Shader
    {
        enum ShaderType
        {
            Vertex,
            Fragment
        };
        enum BufferType
        {
            Static,
            Dynamic
        };

    private:
        BufferType buffer_type;
        ShaderType type;
        char *code;
        GLuint shader;

    public:
        Shader(ShaderType type, const std::string &shader_code)
            : type(type)
        {
            code = (char *) malloc(shader_code.size() + 1);
            code[shader_code.size()] = '\0';
            for (int s = 0; s != strlen(code); ++s)
            {
                code[s] = shader_code[s];
            }
            shader = glCreateShader(type == Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
            glShaderSource(shader, 1, &code, nullptr);
        }
        ~Shader()
        {
            delete[] code;
        }
        GLuint &operator*()
        {
            return shader;
        }
        
        const GLuint &operator*() const
        {
            return shader;
        }

        ShaderType getType() const
        {
            return type;
        }
        void compile()
        {
            glCompileShader(shader);
        }
        void remove()
        {
            glDeleteShader(shader);
        }
        void setBufferType(BufferType type)
        {
            buffer_type = type;
        }
        BufferType getBufferType() const
        {
            return buffer_type;
        }
    };

    class ShaderProgram
    {
        GLuint program = glCreateProgram();
        GLuint points_vbo = 0;
        GLuint colors_vbo = 0;
        GLuint vao = 0;
        std::vector<GLfloat> point_mat3;
        std::vector<GLfloat> color_mat3;

    public:
        ShaderProgram()
        {
        }
        void bindBuffers()
        {
            glGenBuffers(1, &points_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
            glBufferData(GL_ARRAY_BUFFER, point_mat3.size() * sizeof(GLfloat), &point_mat3[0], GL_STATIC_DRAW);
            glGenBuffers(1, &colors_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
            glBufferData(GL_ARRAY_BUFFER, color_mat3.size() * sizeof(GLfloat), &color_mat3[0], GL_STATIC_DRAW);
        
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        }
        void attach(Shader &shader)
        {
            glAttachShader(program, *shader);
        }
        void use()
        {
            glUseProgram(program);
        }
        void link()
        {
            glLinkProgram(program);
        }  
        template<class It>
        void setPoints(It begin, const It &end)
        {
            point_mat3.assign(begin, end);
        }
        template<class It>
        void setPalette(It begin, const It &end)
        {
            color_mat3.assign(begin, end);
        }
    };

    class ShaderBuildSystem
    {
        
        Shader vertex_shader;
        Shader fragment_shader;
        ShaderProgram *program = nullptr;

    public:
        ShaderBuildSystem(const std::string &vertex_shader_code, const std::string &fragment_shader_code);
        void build(ShaderProgram &program);
        ~ShaderBuildSystem();
        void draw();
    };

}
