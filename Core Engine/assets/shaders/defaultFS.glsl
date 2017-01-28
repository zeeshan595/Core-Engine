#version 150

out vec4 FragColor;

in vec3 vertex_position_world;
in vec4 the_color;
in vec2 the_uv;
in vec3 vertex_normal_world;

uniform sampler2D texture_map;

//Light Variables
#define MAX_LIGHTS 10

//Directional
uniform vec3 light_directions[MAX_LIGHTS];
uniform int directional_light_count;
uniform float directional_light_brightness[MAX_LIGHTS];
uniform vec4 directional_light_color[MAX_LIGHTS];

//Point
uniform vec3 light_positions[MAX_LIGHTS];
uniform float light_range[MAX_LIGHTS];
uniform int point_light_count;
uniform float point_light_brightness[MAX_LIGHTS];
uniform vec4 point_light_color[MAX_LIGHTS];

//Camera Position
uniform vec3 camera_position_world;

void main()
{
    //Your allowed to edit these
    vec3 ambient_color  = vec3(0.1f, 0.1f, 0.1f);
    vec3 diffuse_color  = vec3(1.0f, 1.0f, 1.0f);
    vec3 spec_color     = vec3(1.0f, 1.0f, 1.0f);
    float spec_amount   = 2.0f;
    float spec_area     = 80.0f;
    
    //Setup default diffuse and specular values if no light is there
    vec4 diffuse = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec4 specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    //Texture
    vec4 texture = texture(texture_map, the_uv);

    //directional lights
    for (int i = 0; i < directional_light_count; ++i)
    {
        //Diffuse
        float diffuseBrightness = dot(light_directions[i], normalize(vertex_normal_world));
        diffuseBrightness = clamp(diffuseBrightness, 0, 1);
        diffuse += (vec4(diffuse_color, 1.0f) + directional_light_color[i]) * diffuseBrightness * directional_light_brightness[i];

        //Specular
        vec3 reflectedVector = reflect(-light_directions[i], vertex_normal_world);
        vec3 eyeVectorWorld = normalize(camera_position_world - vertex_position_world);
        float specularBrightness = dot(reflectedVector, eyeVectorWorld) * spec_amount;
        specularBrightness = clamp(specularBrightness, 0, 1);
        specularBrightness = pow(specularBrightness, spec_area);
        specular += (vec4(spec_color, 1.0f) + directional_light_color[i]) * specularBrightness * directional_light_brightness[i];
    }
    //Point Lights
    for (int i = 0; i < point_light_count; i++)
    {
        float light_distance_vector = distance(light_positions[i], vertex_position_world);
        //This fucking light formula >> https://imdoingitwrong.wordpress.com/2011/01/31/light-attenuation/
        float light_distance = 1 / ( (1 / light_range[i]) + ( (2 / light_range[i]) *  light_distance_vector) + ( (1 / light_range[i]) * pow(light_distance_vector, 2) ) );
        vec3 light_direction_vector = normalize(light_positions[i] - vertex_position_world);
        //Diffuse
        float diffuseBrightness = dot(light_direction_vector, normalize(vertex_normal_world));
        diffuseBrightness = clamp(diffuseBrightness, 0, 1) * light_distance;
        diffuse += (vec4(diffuse_color, 1.0f) * point_light_color[i]) * diffuseBrightness * point_light_brightness[i];

        //Specular
        vec3 reflectedVector = reflect(-light_direction_vector, vertex_normal_world);
        vec3 eyeVectorWorld = normalize(camera_position_world - vertex_position_world);
        float specularBrightness = dot(reflectedVector, eyeVectorWorld) * spec_amount;
        specularBrightness = clamp(specularBrightness, 0, 1);
        specularBrightness = pow(specularBrightness, spec_area) * light_distance;
        specular += (vec4(spec_color, 1.0f) * point_light_color[i]) * specularBrightness * point_light_brightness[i];
    }
    //Apply
    vec4 light = vec4(ambient_color, 1.0f) + diffuse + specular;
    FragColor = light * texture;
}