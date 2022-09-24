#version 330 core

precision mediump float;

in vec3 v_normal;
in float v_height;

out vec4 FragColor;

void main()
{
    vec3 light = normalize(vec3(1.0f, 1.0f, 1.0f));
    vec3 normal = normalize(v_normal);
    vec3 color = vec3(0.275f, 0.45f, 0.275f);
    if (v_height < 0.2f) {
        color = mix(color, vec3(0.761f, 0.698f, 0.502f), (0.2f - v_height) / 0.2f);
    }
    FragColor = vec4(color * max(0.0f, dot(light, normal)), 1.0f);
}
