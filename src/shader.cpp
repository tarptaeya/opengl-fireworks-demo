#include "shader.h"

namespace shader
{
    GLuint create(GLenum type, const std::string &path)
    {
        std::string source = fs::read(path);
        const char *raw_source = source.c_str();
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &raw_source, nullptr);
        glCompileShader(shader);
        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (!status) {
            char log[512];
            glGetShaderInfoLog(shader, 512, 0, log);
            std::cerr << "[error] failed to compile shader" << std::endl;
            std::cerr << log << std::endl;
        }
        return shader;
    }

    GLuint program(GLuint vertex_shader, GLuint fragment_shader)
    {
        GLuint program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);
        GLint status;
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        if (!status) {
            char log[512];
            glGetProgramInfoLog(program, 512, 0, log);
            std::cerr << "[error] failed to link program" << std::endl;
            std::cerr << log << std::endl;
        }
        return program;
    }
}