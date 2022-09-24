#version 330 core

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec2 a_texcoord;

uniform mat4 u_world;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 v_texcoord;

void main()
{
    gl_Position = u_projection * u_view * u_world * a_position;
    v_texcoord = a_texcoord;
}