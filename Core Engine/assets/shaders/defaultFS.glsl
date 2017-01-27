#version 150

out vec4 FragColor;

in vec3 vertex_position_world;
in vec4 the_color;
in vec2 the_uv;
in vec3 vertex_normal_world;

uniform sampler2D texture_map;

//Light
#define MAX_LIGHTS 10
uniform int directional_light_count;
uniform int point_light_count;
uniform vec3 light_directions[MAX_LIGHTS];
uniform vec3 light_position[MAX_LIGHTS];
uniform vec3 camera_position_world;

void main()
{
    vec3 ambient_color  = vec3(0.1f, 0.1f, 0.1f);
    vec3 diffuse_color  = vec3(1.0f, 1.0f, 1.0f);
    vec3 spec_color     = vec3(1.0f, 1.0f, 1.0f);
    float spec_amount   = 2.0f;
    float spec_area     = 80.0f;
    

    vec4 diffuse = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec4 specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    //Texture
    vec4 texture = texture(texture_map, the_uv);

    //directional light
    for (int i = 0; i < directional_light_count; ++i)
    {
        //Diffuse
        float diffuseBrightness = dot(light_directions[i], normalize(vertex_normal_world));
        diffuseBrightness = clamp(diffuseBrightness, 0, 1);
        diffuse += vec4(diffuse_color, 1.0f) * diffuseBrightness;

        //Specular
        vec3 reflectedVector = reflect(-light_directions[i], vertex_normal_world);
        vec3 eyeVectorWorld = normalize(camera_position_world - vertex_position_world);
        float specularBrightness = dot(reflectedVector, eyeVectorWorld) * spec_amount;
        specularBrightness = clamp(specularBrightness, 0, 1);
        specularBrightness = pow(specularBrightness, spec_area);
        specular += vec4(spec_color, 1.0f) * specularBrightness;
    }
    for (int i = 0; i < point_light_count; i++)
    {
        //Diffuse
        float point_light_range = 10.0f;
        float light_distance = distance(vertex_normal_world, light_position[i]);
        float diffuseBrightness = 1 / (1 + ((1 / point_light_range) * light_distance) + ((1 / pow(point_light_range, 2)) * pow(light_distance, 2)));
        diffuseBrightness = clamp(diffuseBrightness, 0, 1);
        diffuse += vec4(diffuse_color, 1.0f) * diffuseBrightness;
    }
    //Apply
    vec4 light = vec4(ambient_color, 1.0f) + diffuse + specular;
    FragColor = light * texture;
}