#pragma once

#define GL_SILENCE_DEPRECATION

#include "xobject.h"

#include <GL/glew.h>

#include <string>

#define NUM_PARTICLES 50

class Particle
{
public:
    float life = 0.0f;
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 velocity = glm::vec3(0.0f);
};

enum FireworkState
{
    INIT,
    LAUNCHED,
    EXPLODED,
};

class Firework : public XObject
{
    GLuint m_program;
    GLuint m_vertex_array;
    GLuint m_buffer;
    GLuint m_texture;

    GLint m_world_location;
    GLint m_view_location;
    GLint m_projection_location;

    Particle m_particles[NUM_PARTICLES];

    FireworkState m_state = INIT;
    glm::vec3 m_root_position = glm::vec3(0.0f);
    glm::vec3 m_root_position_cached;
    glm::vec3 m_root_velocity;

public:
    explicit Firework(glm::vec3 root_position, const std::string &path);
    ~Firework() override;
    void update(float delta_time) override;
    void render(Camera *camera) override;
};
