#version 150

out vec4 FragColor;

in vec3 vertex_position_world;
in vec4 the_color;
in vec2 the_uv;
in vec3 vertex_normal_world;

uniform sampler2D texture_map;

//Light
uniform vec3 light_ambient;
uniform vec3 light_direction;
uniform vec3 camera_position_world;

void main()
{
    float spec_amount = 2.0f;
    float spec_area = 80.0f;

    //Texture
    vec4 texture = texture(texture_map, the_uv);

    //Diffuse
    float diffuseBrightness = dot(light_direction, normalize(vertex_normal_world));
    diffuseBrightness = clamp(diffuseBrightness, 0, 1);
    vec4 diffuse = vec4(diffuseBrightness, diffuseBrightness, diffuseBrightness, 1.0f);

    //Specular
    vec3 reflectedVector = reflect(-light_direction, vertex_normal_world);
    vec3 eyeVectorWorld = normalize(camera_position_world - vertex_position_world);
    float specularBrightness = dot(reflectedVector, eyeVectorWorld) * spec_amount;
    specularBrightness = clamp(specularBrightness, 0, 1);
    specularBrightness = pow(specularBrightness, spec_area);
    vec4 specular = vec4(specularBrightness, specularBrightness, specularBrightness, 1.0f);

    //Apply
    vec4 light = vec4(light_ambient, 1.0f) + diffuse + specular;
    FragColor = light * texture;
}