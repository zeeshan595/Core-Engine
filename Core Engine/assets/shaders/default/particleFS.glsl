#version 450

out vec4 FragColor;

in vec2 the_uv;

uniform sampler2D texture_map0;

void main()
{
    FragColor = texture(texture_map0, the_uv);
}