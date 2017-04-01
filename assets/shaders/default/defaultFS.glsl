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

    vec4 texture_color  = texture(texture_map0, the_vertex_uv);
    out_color           = (vec4(total_diffuse, 1.0f) * texture_color) + vec4(total_specular, 1.0f);
}