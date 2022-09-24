#pragma once

#define GL_SILENCE_DEPRECATION

#include <GL/glew.h>
#include "stb_image.h"

#include <iostream>

namespace texture
{
    GLuint create(const std::string &path, GLint wrap = GL_CLAMP_TO_EDGE);
}