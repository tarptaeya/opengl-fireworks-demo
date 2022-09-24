#version 330 core

precision mediump float;

in vec2 v_texcoord;
in float v_distance;

uniform sampler2D u_bump_map;

uniform float u_time;

out vec4 FragColor;

void main()
{
    vec3 color = vec3(0.2f, 0.4f, 0.6f);
    vec3 bump = texture(u_bump_map, v_texcoord - vec2(0.02, 0.02) * u_time).rgb;
    color = mix(color, bump, 0.2f);
    FragColor = vec4(color, 1.0f);

}