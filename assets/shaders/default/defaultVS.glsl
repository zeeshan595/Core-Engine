#version 150
#define MAX_LIGHTS 4

in vec3 vertex_position;
in vec4 vertex_color;
in vec2 vertex_uv;
in vec3 vertex_normal;
in vec3 vertex_tangent;

out vec2 the_vertex_uv;
out vec3 the_vertex_normal;
out vec3 camera_vector;
out vec3 the_directional_light_vector[MAX_LIGHTS];
out vec3 the_directional_light_color[MAX_LIGHTS];
out vec3 the_point_light_direction[MAX_LIGHTS];
out vec3 the_point_light_color[MAX_LIGHTS];
out float the_point_light_range[MAX_LIGHTS];

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 transform_matrix;

//Lighting
uniform vec3 directional_light_direction[MAX_LIGHTS];
uniform vec3 directional_light_color[MAX_LIGHTS];

uniform vec3 point_light_position[MAX_LIGHTS];
uniform vec3 point_light_color[MAX_LIGHTS];
uniform float point_light_range[MAX_LIGHTS];

void main()
{
    vec4 vertex_position_world = transform_matrix * vec4(vertex_position, 1.0f);
    gl_Position = projection_matrix * view_matrix * vertex_position_world;
    the_vertex_uv = vertex_uv;

    the_vertex_normal = (transform_matrix * vec4(vertex_normal, 0.0f)).xyz;
    camera_vector = (inverse(view_matrix) * vec4(1.0f)).xyz - vertex_position_world.xyz;

    the_directional_light_vector    = directional_light_direction;
    the_directional_light_color     = directional_light_color;

    for (int i = 0; i < MAX_LIGHTS; i++)
    the_point_light_direction[i]    = point_light_position[i] - vertex_position_world.xyz;

    the_point_light_color           = point_light_color;
    the_point_light_range           = point_light_range;
}