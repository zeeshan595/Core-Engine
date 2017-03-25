#version 150

in vec3 vertex_position;
in vec4 vertex_color;
in vec2 vertex_uv;
in vec3 vertex_normal;
in vec3 vertex_tangent;

out vec3 vertex_position_world;
out vec4 the_vertex_color;
out vec2 the_vertex_uv;
out vec3 normal;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 transform_matrix;

void main()
{
    vec4 v = vec4(vertex_position, 1.0f);
    mat4 mvp_matrix = (projection_matrix * view_matrix * transform_matrix);
    gl_Position = mvp_matrix * v;

    vertex_position_world = vec3(transform_matrix * v);
    the_vertex_color = vertex_color;
    the_vertex_uv = vertex_uv;
    normal = vec3(transform_matrix * vec4(vertex_normal, 1.0f));
}