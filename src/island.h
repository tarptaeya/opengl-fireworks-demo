#pragma once

#define GL_SILENCE_DEPRECATION

#include "xobject.h"

#include <GL/glew.h>

#include <string>
#include <vector>

class Island : public XObject
{
    GLuint m_program;
    GLuint m_vertex_array;
    GLuint m_buffer;

    GLint m_model_location;
    GLint m_view_location;
    GLint m_projection_location;
    GLint m_model_inverse_transpose_location;

    glm::mat4 m_model;
    int m_num_elements;

    std::vector<std::vector<int>> m_height_data;

public:
    explicit Island();
    ~Island() override;
    void update(float delta_time) override;
    void render(Camera *camera) override;

private:
    void init_height_data(const std::string &height_map);
};