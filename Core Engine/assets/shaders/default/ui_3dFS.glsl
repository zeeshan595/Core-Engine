#version 150

out vec4 FragColor;

in vec2 the_uv;

uniform sampler2D texture_map0;

void main()
{
    if (texture(texture_map0, the_uv).a != 1.0f)
        discard;
    FragColor = texture(texture_map0, the_uv);
}