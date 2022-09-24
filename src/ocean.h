#pragma once

#define GL_SILENCE_DEPRECATION

#include "xobject.h"

#include <GL/glew.h>

class Ocean : public XObject
{
    GLuint m_program;
    GLuint m_vertex_array;
    GLuint m_buffer;
    GLuint m_texture;

    GLint m_world_location;
    GLint m_view_location;
    GLint m_projection_location;
    GLint m_time_location;
    
    int m_triangles = 0;
    float m_time = 0.0f;
    glm::mat4 m_world;
public:
    explicit Ocean();
    ~Ocean() override;
    void update(float delta_time) override;
    void render(Camera *camera) override;
};