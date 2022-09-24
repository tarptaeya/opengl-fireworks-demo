#include "ocean.h"
#include "shader.h"
#include "texture.h"

#include <vector>

Ocean::Ocean()
{
    GLuint vertex_shader = shader::create(GL_VERTEX_SHADER, "res/shaders/ocean.vertex.glsl");
    GLuint fragment_shader = shader::create(GL_FRAGMENT_SHADER, "res/shaders/ocean.fragment.glsl");
    m_program = shader::program(vertex_shader, fragment_shader);

    m_texture = texture::create("res/textures/water-bump-1.jpg", GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glGenVertexArrays(1, &m_vertex_array);
    glBindVertexArray(m_vertex_array);

    std::vector<float> vertices;
    int size = 4;
    for (int x = -size; x < size; ++x) {
        for (int z = -size; z < size; ++z) {
            vertices.push_back(x);
            vertices.push_back(z);
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);

            vertices.push_back(x);
            vertices.push_back(z + 1.0f);
            vertices.push_back(0.0f);
            vertices.push_back(1.0f);

            vertices.push_back(x + 1.0f);
            vertices.push_back(z);
            vertices.push_back(1.0f);
            vertices.push_back(0.0f);

            vertices.push_back(x);
            vertices.push_back(z + 1.0f);
            vertices.push_back(0.0f);
            vertices.push_back(1.0f);

            vertices.push_back(x + 1.0f);
            vertices.push_back(z + 1.0f);
            vertices.push_back(1.0f);
            vertices.push_back(1.0f);

            vertices.push_back(x + 1.0f);
            vertices.push_back(z);
            vertices.push_back(1.0f);
            vertices.push_back(0.0f);

            m_triangles += 2;
        }
    }

    glGenBuffers(1, &m_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void *) (2 * sizeof(float)));

    m_world_location = glGetUniformLocation(m_program, "u_world");
    m_view_location = glGetUniformLocation(m_program, "u_view");
    m_projection_location = glGetUniformLocation(m_program, "u_projection");
    m_time_location = glGetUniformLocation(m_program, "u_time");

    m_world = glm::mat4(1.0f);
    m_world = glm::scale(m_world, glm::vec3(5.0f, 1.0f, 5.0f));

    glBindVertexArray(0);
}

Ocean::~Ocean()
{
    glDeleteProgram(m_program);
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_buffer);
}

void Ocean::update(float delta_time)
{
    m_time += delta_time;
}

void Ocean::render(Camera *camera)
{
    glUseProgram(m_program);
    glBindVertexArray(m_vertex_array);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glUniformMatrix4fv(m_world_location, 1, GL_FALSE, glm::value_ptr(m_world));
    glUniformMatrix4fv(m_view_location, 1, GL_FALSE, glm::value_ptr(camera->view()));
    glUniformMatrix4fv(m_projection_location, 1, GL_FALSE, glm::value_ptr(camera->projection()));
    glUniform1f(m_time_location, m_time);
    glDrawArrays(GL_TRIANGLES, 0, 3 * m_triangles);
    glBindVertexArray(0);
}