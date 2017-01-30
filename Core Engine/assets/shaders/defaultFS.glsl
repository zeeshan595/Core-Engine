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
    float spec_amount   = 1.5f;
    float spec_area     = 80.0f;
    
    //Setup default diffuse and specular values if no light is there
    vec4 diffuse = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec4 specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    //Texture
    vec4 texture = texture(texture_map, the_uv);

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
        point_light_formula = point_light_formula * 10.0f;

        //Calculate diffuse lighting
        float diffuse_brightness = dot(normalize(point_light_direction), normalize(vertex_normal_world));
        diffuse_brightness = clamp(diffuse_brightness, 0, 1);
        //Apply results
        vec4 apply_diffuse_color = vec4(diffuse_color, 1.0f) + point_light_color[i];
        diffuse += apply_diffuse_color * diffuse_brightness * point_light_brightness[i] * point_light_formula;
    
        //Calculate light's reflected vector & camera viewing vector
        vec3 reflect_vector = reflect(-normalize(point_light_direction), normalize(vertex_normal_world));
        vec3 eye_vector = normalize(camera_position_world - vertex_position_world);
        //Calculate specular lighting
        float specular_brightness = dot(reflect_vector, eye_vector) * spec_amount;
        specular_brightness = clamp(specular_brightness, 0, 1);
        //Make the result less bright by using pow (between 0-1)
        specular_brightness = pow(specular_brightness, spec_area);
        //Apply results
        vec4 apply_spec_color = vec4(spec_color, 1.0f) + point_light_color[i];
        specular += apply_spec_color * specular_brightness * point_light_brightness[i] * point_light_formula;
    }
    //Apply Texture and Light
    vec4 light = vec4(ambient_color, 1.0f) + diffuse + specular;
    FragColor = light * texture;
}