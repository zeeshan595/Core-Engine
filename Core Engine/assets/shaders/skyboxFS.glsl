#version 150

out vec4 FragColor;

in vec3 the_uv;

uniform samplerCube cube_map;

void main()
{
    FragColor = vec4(1.0f);//texture(cube_map, the_uv);
}