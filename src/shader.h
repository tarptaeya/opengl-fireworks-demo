#pragma once

#define GL_SILENCE_DEPRECATION

#include "fs.h"

#include <GL/glew.h>

#include <iostream>
#include <string>

namespace shader
{
    GLuint create(GLenum type, const std::string &path);

    GLuint program(GLuint vertex_shader, GLuint fragment_shader);
}