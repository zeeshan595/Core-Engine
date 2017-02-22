#version 150

out vec4 FragColor;

in vec2 the_uv;
in vec3 vertex_position_world;

uniform sampler2D texture_map0;
//Camera Position
uniform vec3 camera_position_world;

//Fog
uniform float fog_distance;
uniform float fog_density;
uniform float fog_gradient;
uniform vec4 fog_color;

void main()
{
    if (texture(texture_map0, the_uv).a != 1.0f)
        discard;

    //Fog
    float distance_from_camera = distance(camera_position_world, vertex_position_world);
    distance_from_camera = distance_from_camera * fog_distance;
    float fog = exp(-pow(distance_from_camera * fog_density, fog_gradient));
    fog = clamp(fog, 0.0f, 1.0f);
    FragColor = mix(fog_color, texture(texture_map0, the_uv), fog);
}