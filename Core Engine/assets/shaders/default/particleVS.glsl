#version 450

in vec3 vertex_position_model;
in vec4 vertex_color;
in vec2 vertex_uv;

uniform mat4 view_projection_matrix;
uniform mat4 world_matrices[100000];

void main()
{
    mat4 mvp_matrix =  world_matrices[gl_InstanceID];
    vec4 v = vec4(vertex_position_model, 1.0f);
    gl_Position = view_projection_matrix * v;
}