#include "firework.h"
#include "shader.h"
#include "texture.h"

#include <glm/gtc/random.hpp>

Firework::Firework(glm::vec3 root_position, const std::string &path)
    : m_root_position_cached(root_position)
{
    GLuint vertex_shader = shader::create(GL_VERTEX_SHADER, "res/shaders/firework.vertex.glsl");
    GLuint fragment_shader = shader::create(GL_FRAGMENT_SHADER, "res/shaders/firework.fragment.glsl");
    m_program = shader::program(vertex_shader, fragment_shader);

    m_texture = texture::create(path);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glGenVertexArrays(1, &m_vertex_array);
    glBindVertexArray(m_vertex_array);

    float vertices[] = {
        -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 0.0f,
    };
    glGenBuffers(1, &m_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    m_world_location = glGetUniformLocation(m_program, "u_world");
    m_view_location = glGetUniformLocation(m_program, "u_view");
    m_projection_location = glGetUniformLocation(m_program, "u_projection");

    glBindVertexArray(0);
}

Firework::~Firework()
{
}

void Firework::update(float delta_time)
{
    if (m_state == INIT) {
        m_root_position = glm::vec3(m_root_position_cached);
        m_root_velocity = glm::vec3(glm::gaussRand(-0.2f, 0.2f), 2.5f, glm::gaussRand(-0.2f, 0.2f));
        for (int i = 0; i < NUM_PARTICLES; ++i) {
            m_particles[i].position = glm::vec3(0.0f);
            m_particles[i].life = 0.0f;
            m_particles[i].velocity = 0.5f * glm::vec3(glm::gaussRand(0.0f, 1.0f), glm::gaussRand(0.0f, 1.0f), glm::gaussRand(0.0f, 1.0f));
        }

        if (rand() / (float) RAND_MAX < 0.02f)
            m_state = LAUNCHED;
    } else if (m_state == LAUNCHED) {
        m_root_position += delta_time * m_root_velocity;
        if (glm::length(m_root_position - m_root_position_cached) > 4.0f) {
            m_state = EXPLODED;
        }
    } else if (m_state == EXPLODED) {
        int count = 0;

        for (int i = 0; i < NUM_PARTICLES; ++i) {
            m_particles[i].life += delta_time;
            m_particles[i].position += delta_time * m_particles[i].velocity;
            m_particles[i].velocity.y -= 2.0f * delta_time;

            if (m_particles[i].life > 2.0f) ++count;
        }

        if (count == NUM_PARTICLES) {
            m_state = INIT;
        }
    }
}

void Firework::render(Camera *camera)
{
    glm::mat4 view = camera->view();
    view = view - glm::mat4(glm::mat3(view));
    view[0][0] = view[1][1] = view[2][2] = view[3][3] = 1.0f;

    glUseProgram(m_program);
    glBindVertexArray(m_vertex_array);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glUniformMatrix4fv(m_view_location, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(m_projection_location, 1, GL_FALSE, glm::value_ptr(camera->projection()));

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    if (m_state == INIT) {

    } else if (m_state == LAUNCHED) {
        glm::mat4 S = glm::scale(glm::mat4(1.0f), 0.25f * glm::vec3(1.0f));
        glm::mat4 T = glm::translate(glm::mat4(1.0f), m_root_position);
        glUniformMatrix4fv(m_world_location, 1, GL_FALSE, glm::value_ptr(T * S));
        glDrawArrays(GL_TRIANGLES, 0, 6);
    } else if (m_state == EXPLODED) {
        for (int i = 0; i < NUM_PARTICLES; ++i) {
            Particle particle = m_particles[i];
            glm::mat4 S = glm::scale(glm::mat4(1.0f), 0.1f / (1.0f + particle.life) * glm::vec3(1.0f));
            glm::mat4 T = glm::translate(glm::mat4(1.0f), particle.position + m_root_position);
            glUniformMatrix4fv(m_world_location, 1, GL_FALSE, glm::value_ptr(T * S));
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindVertexArray(0);
}