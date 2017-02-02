#version 150

out vec4 FragColor;

in vec3 the_uv;

uniform samplerCube cube_map;
uniform vec4 fog_color;

const float lower_limit = 0.0f;
const float upper_limit = 50.0f;

void main()
{
    vec4 texture_color = texture(cube_map, the_uv);

    float factor = (the_uv.y - lower_limit) / (upper_limit - lower_limit);
    factor = clamp(factor, 0.0f, 1.0f);
    FragColor = mix(fog_color, texture_color, factor);
}