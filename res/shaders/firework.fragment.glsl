#version 330 core

in vec2 v_texcoord;

uniform sampler2D u_texture;

out vec4 FragColor;

void main()
{
    vec4 color = texture(u_texture, v_texcoord);
    if (color.a < 0.2) discard;
    FragColor = color;
}