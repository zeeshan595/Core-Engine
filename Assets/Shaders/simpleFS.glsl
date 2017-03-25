#version 150

out vec4 FragColor;

in vec3 vertex_position_world;
in vec4 the_vertex_color;
in vec2 the_vertex_uv;
in mat3 tangent_to_world_matrix;

uniform sampler2D texture_map0; //Texture
uniform sampler2D texture_map1; //Normal Texture

//Camera Position
uniform vec3 camera_position;

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

//Fog
uniform float fog_distance;
uniform float fog_density;
uniform float fog_gradient;
uniform vec4 fog_color;

void main()
{
    if (texture(texture_map0, the_vertex_uv).w < 0.3f)
        discard;

    //Your allowed to edit these
    vec3 ambient_color  = vec3(0.1f, 0.1f, 0.1f);
    vec3 diffuse_color  = vec3(0.3f, 0.3f, 0.3f);
    vec3 spec_color     = vec3(1.0f, 1.0f, 1.0f);
    float spec_amount   = 1.0f;
    float spec_area     = 150.0f;
    
    //Setup default diffuse and specular values if no light is there
    vec4 diffuse = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec4 specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    //Texture
    vec4 texture_map = texture(texture_map0, the_vertex_uv);
    //Normal Texture
    vec4 normal_map = texture(texture_map1, the_vertex_uv);
    //Convert color to coordinates
    normal_map = (normal_map * 2) - vec4(1.0f, 1.0f, 1.0f, 1.0f);
    //tangent space -> model space
    vec3 normal = tangent_to_world_matrix * normal_map.xyz;

    //directional lights
    for (int i = 0; i < directional_light_count; ++i)
    {
        //Calculate diffuse lighting
        float diffuse_brightness = dot(normalize(light_directions[i]), normalize(normal));
        diffuse_brightness = clamp(diffuse_brightness, 0, 1);
        //Apply results
        vec4 apply_diffuse_color = vec4(diffuse_color, 1.0f) + directional_light_color[i];
        diffuse += apply_diffuse_color * diffuse_brightness * directional_light_brightness[i];
    
        //Calculate light's reflected vector & camera viewing vector
        vec3 reflect_vector = reflect(normalize(normal), normalize(light_directions[i]));
        vec3 eye_vector = normalize(camera_position - vertex_position_world);
        //Calculate specular lighting
        float specular_brightness = dot(reflect_vector, eye_vector) * spec_amount;
        specular_brightness = clamp(specular_brightness, 0, 1);
        //Make the result less bright by using pow (between 0-1)
        specular_brightness = pow(specular_brightness, spec_area);
        //Apply results
        vec4 apply_spec_color = vec4(spec_color, 1.0f) + directional_light_color[i];
        specular += apply_spec_color * specular_brightness * directional_light_brightness[i] * texture(texture_map1, the_vertex_uv).w;
    }
    //Point Lights
    for (int i = 0; i < point_light_count; i++)
    {
        //Calculate point light variables
        vec3 point_light_direction = normalize(light_positions[i] - vertex_position_world);
        float distance_from_light = distance(light_positions[i], vertex_position_world);
        float point_light_formula = 1 / ( (1 / light_range[i]) + ( (2 / light_range[i]) * distance_from_light ) + ( (1 / pow(light_range[i], 2)) + pow(distance_from_light, 2) ) );

        //Calculate diffuse lighting
        float diffuse_brightness = dot(normalize(normal), normalize(point_light_direction));
        diffuse_brightness = clamp(diffuse_brightness, 0.0f, 1.0f);
        //Apply results
        vec4 apply_diffuse_color = vec4(diffuse_color, 1.0f) + point_light_color[i];
        diffuse += apply_diffuse_color * diffuse_brightness * point_light_brightness[i] * point_light_formula;
    
        //Calculate light's reflected vector & camera viewing vector
        vec3 reflect_vector = reflect(-normalize(point_light_direction), normalize(normal));
        vec3 eye_vector = normalize(camera_position - vertex_position_world);
        //Calculate specular lighting
        float specular_brightness = dot(reflect_vector, eye_vector) * spec_amount;
        specular_brightness = clamp(specular_brightness, 0.0f, 1.0f);
        //Make the result less bright by using pow (between 0-1)
        specular_brightness = pow(specular_brightness, spec_area);
        //Apply results
        vec4 apply_spec_color = vec4(spec_color, 1.0f) + point_light_color[i];
        specular += apply_spec_color * specular_brightness * point_light_brightness[i] * point_light_formula * texture(texture_map1, the_vertex_uv).w;
    }
    //Combine all light calculations
    vec4 light = vec4(ambient_color, 1.0f) + diffuse + specular;
    //Fog
    float distance_from_camera = distance(camera_position, vertex_position_world);
    distance_from_camera = distance_from_camera * fog_distance;
    float fog = exp(-pow(distance_from_camera * fog_density, fog_gradient));
    fog = clamp(fog, 0.0f, 1.0f);
    FragColor = mix(fog_color, light * texture_map, fog);
}