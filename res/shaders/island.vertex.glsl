#version 330 core

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec3 a_normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat3 u_model_inverse_transpose;

out vec3 v_normal;
out float v_height;

void main()
{
    gl_Position = u_projection * u_view * u_model * a_position;
    v_normal = normalize(u_model_inverse_transpose * a_normal);
    v_height = (u_model * a_position).y;
}
