#version 150

out vec4 FragColor;

in vec3 vertex_position_world;
in vec4 the_color;
in vec2 the_uv;
in vec3 vertex_normal_world;

//terrain maps
uniform sampler2D texture_map0;//blend map

uniform sampler2D texture_map1;
uniform sampler2D texture_map2;
uniform sampler2D texture_map3;
uniform sampler2D texture_map4;

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

//Fog
uniform float fog_distance;
uniform float fog_density;
uniform float fog_gradient;
uniform vec4 fog_color;

void main()
{
    //Your allowed to edit these
    float terrain_tile_amount = 80.0f;
    vec3 ambient_color  = vec3(0.1f, 0.1f, 0.1f);
    vec3 diffuse_color  = vec3(1.0f, 1.0f, 1.0f);
    vec3 spec_color     = vec3(1.0f, 1.0f, 1.0f);
    float spec_amount   = 0.1f;
    float spec_area     = 150.0f;
    
    //Setup default diffuse and specular values if no light is there
    vec4 diffuse = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec4 specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    //Textures
    vec4 blend_map = texture(texture_map0, the_uv);
    float black_amount = 1 - (blend_map.r + blend_map.g + blend_map.b);
    
    vec2 tiled_uv = the_uv * terrain_tile_amount;
    vec4 texture0 = texture(texture_map1, tiled_uv) * black_amount;
    vec4 texture1 = texture(texture_map2, tiled_uv) * blend_map.r;
    vec4 texture2 = texture(texture_map3, tiled_uv) * blend_map.g;
    vec4 texture3 = texture(texture_map4, tiled_uv) * blend_map.b;

    vec4 texture = texture0 + texture1 + texture2 + texture3;

    //directional lights
    for (int i = 0; i < directional_light_count; ++i)
    {
        //Calculate diffuse lighting
        float diffuse_brightness = dot(normalize(light_directions[i]), normalize(vertex_normal_world));
        diffuse_brightness = clamp(diffuse_brightness, 0, 1);
        //Apply results
        vec4 apply_diffuse_color = vec4(diffuse_color, 1.0f) + directional_light_color[i];
        diffuse += apply_diffuse_color * diffuse_brightness * directional_light_brightness[i];
    
        //Calculate light's reflected vector & camera viewing vector
        vec3 reflect_vector = reflect(normalize(vertex_normal_world), normalize(light_directions[i]));
        vec3 eye_vector = normalize(camera_position_world - vertex_position_world);
        //Calculate specular lighting
        float specular_brightness = dot(reflect_vector, eye_vector) * spec_amount;
        specular_brightness = clamp(specular_brightness, 0, 1);
        //Make the result less bright by using pow (between 0-1)
        specular_brightness = pow(specular_brightness, spec_area);
        //Apply results
        vec4 apply_spec_color = vec4(spec_color, 1.0f) + directional_light_color[i];
        specular += apply_spec_color * specular_brightness * directional_light_brightness[i];
    }
    //Point Lights
    for (int i = 0; i < point_light_count; i++)
    {
        //Calculate point light variables
        vec3 point_light_direction = normalize(light_positions[i] - vertex_position_world);
        float distance_from_light = distance(light_positions[i], vertex_position_world);
        float point_light_formula = 1 / ( (1 / light_range[i]) + ( (2 / light_range[i]) * distance_from_light ) + ( (1 / pow(light_range[i], 2)) + pow(distance_from_light, 2) ) );

        //Calculate diffuse lighting
        float diffuse_brightness = dot(normalize(vertex_normal_world), normalize(point_light_direction));
        diffuse_brightness = clamp(diffuse_brightness, 0.0f, 1.0f);
        //Apply results
        vec4 apply_diffuse_color = vec4(diffuse_color, 1.0f) + point_light_color[i];
        diffuse += apply_diffuse_color * diffuse_brightness * point_light_brightness[i] * point_light_formula;
    
        //Calculate light's reflected vector & camera viewing vector
        vec3 reflect_vector = reflect(-normalize(point_light_direction), normalize(vertex_normal_world));
        vec3 eye_vector = normalize(camera_position_world - vertex_position_world);
        //Calculate specular lighting
        float specular_brightness = dot(reflect_vector, eye_vector) * spec_amount;
        specular_brightness = clamp(specular_brightness, 0.0f, 1.0f);
        //Make the result less bright by using pow (between 0-1)
        specular_brightness = pow(specular_brightness, spec_area);
        //Apply results
        vec4 apply_spec_color = vec4(spec_color, 1.0f) + point_light_color[i];
        specular += apply_spec_color * specular_brightness * point_light_brightness[i] * point_light_formula;
    }
    //Combine all light calculations
    vec4 light = vec4(ambient_color, 1.0f) + diffuse + specular;
    //Fog
    float distance_from_camera = distance(camera_position_world, vertex_position_world);
    distance_from_camera = distance_from_camera * fog_distance;
    float fog = exp(-pow(distance_from_camera * fog_density, fog_gradient));
    fog = clamp(fog, 0.0f, 1.0f);

    FragColor = mix(fog_color, light * texture, fog);
}