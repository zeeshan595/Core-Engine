#version 150

out vec4 FragColor;

in vec2 the_uv;

uniform sampler2D texture_map;

void main()
{
    FragColor = vec4(1.0f, 0.1f, 0.1f, 1.0f) * texture(texture_map, the_uv);
}