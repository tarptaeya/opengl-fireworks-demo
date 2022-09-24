#include "island.h"
#include "shader.h"
#include "stb_image.h"

int _clamp(int x, int m, int M)
{
    return std::min(std::max(x, m), M);
}

float _height_at(const std::vector<std::vector<int>> &m_height_data, int x, int z)
{
    x = _clamp(x, 0, m_height_data[0].size() - 1);
    z = _clamp(z, 0, m_height_data.size() - 1);

    float half_width = m_height_data[0].size() / 2.0f;
    float half_height = m_height_data.size() / 2.0f;
    float dx = abs(x - half_width) / half_width;
    float dz = abs(z - half_height) / half_height;

    float len = dx * dx + dz * dz;
    if (len > 1.0f)
        len = 1.0f;
    return (1.0f - len) * m_height_data[z][x] / 255.0f;
}

void _add_vertex(std::vector<float> &vertices, int x, int z, std::vector<std::vector<int>> &m_height_data)
{
    std::tuple<float, float, float> v = {x, _height_at(m_height_data, x, z), z};
    glm::vec3 P = glm::vec3(0.0f, _height_at(m_height_data, x, z + 1) - _height_at(m_height_data, x, z - 1), 2.0f);
    glm::vec3 Q = glm::vec3(2.0f, _height_at(m_height_data, x + 1, z) - _height_at(m_height_data, x - 1, z), 0.0f);
    glm::vec3 N = glm::normalize(glm::cross(P, Q));

    vertices.push_back(std::get<0>(v));
    vertices.push_back(std::get<1>(v));
    vertices.push_back(std::get<2>(v));
    vertices.push_back(N.x);
    vertices.push_back(N.y);
    vertices.push_back(N.z);
}

Island::Island()
{
    init_height_data("res/textures/water-bump-2.png");
    int height = m_height_data.size();
    int width = m_height_data[0].size();

    GLuint vertex_shader = shader::create(GL_VERTEX_SHADER, "res/shaders/island.vertex.glsl");
    GLuint fragment_shader = shader::create(GL_FRAGMENT_SHADER, "res/shaders/island.fragment.glsl");
    m_program = shader::program(vertex_shader, fragment_shader);

    glGenVertexArrays(1, &m_vertex_array);
    glBindVertexArray(m_vertex_array);

    m_num_elements = 0;

    std::vector<float> vertices;
    for (int x = 0; x < width; ++x) {
        for (int z = 0; z < height; ++z) {
            _add_vertex(vertices, x, z, m_height_data);
            _add_vertex(vertices, x, z + 1, m_height_data);
            _add_vertex(vertices, x + 1, z, m_height_data);

            _add_vertex(vertices, x, z + 1, m_height_data);
            _add_vertex(vertices, x + 1, z + 1, m_height_data);
            _add_vertex(vertices, x + 1, z, m_height_data);

            m_num_elements += 6;
        }
    }

    glGenBuffers(1, &m_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void *) (3 * sizeof(float)));

    m_model = glm::mat4(1.0f);
    m_model = glm::scale(m_model, 1.0f * glm::vec3(10.0f / width, 0.6f, 10.0f / height));
    m_model = glm::translate(m_model, glm::vec3(-width / 2.0f, 0.0f, -height / 2.0f));

    m_model_location = glGetUniformLocation(m_program, "u_model");
    m_view_location = glGetUniformLocation(m_program, "u_view");
    m_projection_location = glGetUniformLocation(m_program, "u_projection");
    m_model_inverse_transpose_location = glGetUniformLocation(m_program, "u_model_inverse_transpose");

    glBindVertexArray(0);
}

Island::~Island()
{
    glDeleteProgram(m_program);
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_buffer);
}

void Island::init_height_data(const std::string &height_map)
{
    int width, height, channels;
    stbi_uc *data = stbi_load(height_map.c_str(), &width, &height, &channels, 0);
    for (int j = 0; j < height; ++j) {
        m_height_data.push_back(std::vector<int>(width));
        for (int i = 0; i < width; ++i) {
            m_height_data[j][i] = data[(j * width + i) * channels];
        }
    }
    stbi_image_free(data);
}

void Island::update(float delta_time)
{
}

void Island::render(Camera *camera)
{
    glm::mat3 model_inverse_transpose = glm::mat3(glm::transpose(glm::inverse(m_model)));
    glUseProgram(m_program);
    glBindVertexArray(m_vertex_array);
    glUniformMatrix4fv(m_model_location, 1, false, glm::value_ptr(m_model));
    glUniformMatrix4fv(m_view_location, 1, false, glm::value_ptr(camera->view()));
    glUniformMatrix4fv(m_projection_location, 1, false, glm::value_ptr(camera->projection()));
    glUniformMatrix3fv(m_model_inverse_transpose_location, 1, false, glm::value_ptr(model_inverse_transpose));
    glDrawArrays(GL_TRIANGLES, 0, m_num_elements);
    glBindVertexArray(0);
}