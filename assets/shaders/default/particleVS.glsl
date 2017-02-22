#version 150

in vec3 vertex_position_model;
in vec4 vertex_color;
in vec2 vertex_uv;
in vec3 vertex_normal_model;

out vec2 the_uv;

uniform mat4 view_projection_matrix;
uniform mat4 world_matrices[100];

void main()
{
    the_uv = vertex_uv;

    mat4 world_matrix = world_matrices[gl_InstanceID];
    mat4 mvp_matrix = view_projection_matrix * world_matrix;
    vec4 v = vec4(vertex_position_model, 1.0f);
    gl_Position = mvp_matrix * v;
}