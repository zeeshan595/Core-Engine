#version 150

out vec4 FragColor;

in vec2 the_uv;

uniform sampler2D texture_map;

void main()
{
    //Texture
    vec4 texture = texture(texture_map, the_uv);
    FragColor = texture;
}