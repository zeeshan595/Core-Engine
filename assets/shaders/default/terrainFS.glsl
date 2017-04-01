#version 150
#define MAX_LIGHTS 4

out vec4 out_color;

in vec2 the_vertex_uv;
in vec3 the_vertex_normal;
in vec3 camera_vector;
in vec3 the_directional_light_vector[MAX_LIGHTS];
in vec3 the_directional_light_color[MAX_LIGHTS];
in vec3 the_point_light_direction[MAX_LIGHTS];
in vec3 the_point_light_color[MAX_LIGHTS];
in float the_point_light_range[MAX_LIGHTS];

uniform sampler2D texture_map0;
uniform sampler2D texture_map1;
uniform sampler2D texture_map2;
uniform sampler2D texture_map3;
uniform sampler2D texture_map4;

uniform float shine_damper;
uniform float light_reflectivity;

void main()
{
    vec3 diffuse = vec3(0.0f);

    vec3 unit_normal        = normalize(the_vertex_normal);
    vec3 unit_camera_vector = normalize(camera_vector);

    vec3 total_diffuse  = vec3(0.0f);
    vec3 total_specular = vec3(0.0f);

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        //Directional Light
        {
            vec3 unit_light_vector          = normalize(the_directional_light_vector[i]);

            //Diffuse
            float nDot1                     = dot(unit_normal, unit_light_vector);
            float brightness                = max(nDot1, 0.0f);
            vec3  diffuse                   = brightness * the_directional_light_color[i];
            
            //Specular
            vec3  light_direction           = -unit_light_vector;
            vec3  reflected_light_vector    = reflect(light_direction, unit_normal);
            float specular_factor           = dot(reflected_light_vector, unit_camera_vector);
                specular_factor             = max(specular_factor, 0.0f);
            float damped_factor             = pow(specular_factor, shine_damper);
            vec3  final_specular            = damped_factor * light_reflectivity * the_directional_light_color[i];

            total_diffuse   += diffuse;
            total_specular  += final_specular;
        }
        //Point Light
        {
            //Calculate point light variables
            float distance_from_light   = length(the_point_light_direction[i]);
            float point_light_inertia   = 1 / ( (1 / the_point_light_range[i]) + 
            ( (2 / the_point_light_range[i]) * distance_from_light ) + 
            ( (1 / pow(the_point_light_range[i], 2)) + 
            pow(distance_from_light, 2) ) );

            vec3 unit_light_vector          = normalize(the_point_light_direction[i]);

            //Diffuse
            float nDot1                     = dot(unit_normal, unit_light_vector);
            float brightness                = max(nDot1, 0.0f);
            vec3  diffuse                   = brightness * the_point_light_color[i];
            
            //Specular
            vec3  light_direction           = -unit_light_vector;
            vec3  reflected_light_vector    = reflect(light_direction, unit_normal);
            float specular_factor           = dot(reflected_light_vector, unit_camera_vector);
                specular_factor             = max(specular_factor, 0.0f);
            float damped_factor             = pow(specular_factor, shine_damper);
            vec3  final_specular            = damped_factor * light_reflectivity * the_point_light_color[i];

            total_diffuse   += diffuse;
            total_specular  += final_specular;
        }
    }
    //Ambient Light
    total_diffuse       = max(total_diffuse, 0.3f);

    //Textures
    float terrain_tile_amount = 100.0f;

    vec4 blend_map = texture(texture_map0, the_vertex_uv);
    float black_amount = 1 - (blend_map.r + blend_map.g + blend_map.b);
    
    vec2 tiled_uv = the_vertex_uv * terrain_tile_amount;
    vec4 texture0 = texture(texture_map1, tiled_uv) * black_amount;
    vec4 texture1 = texture(texture_map2, tiled_uv) * blend_map.r;
    vec4 texture2 = texture(texture_map3, tiled_uv) * blend_map.g;
    vec4 texture3 = texture(texture_map4, tiled_uv) * blend_map.b;

    vec4 texture_color = texture0 + texture1 + texture2 + texture3;


    out_color           = (vec4(total_diffuse, 1.0f) * texture_color) + vec4(total_specular, 1.0f);
}