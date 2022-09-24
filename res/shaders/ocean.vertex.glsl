#version 330 core

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec2 a_texcoord;

uniform mat4 u_world;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 v_texcoord;
out float v_distance;

void main()
{
    vec4 position = vec4(a_position);
    position.z = position.y;
    position.y = 0.05f;
    gl_Position = u_projection * u_view * u_world * position;
    v_texcoord = a_texcoord;
    v_distance = length(u_view * u_world * a_position);
}