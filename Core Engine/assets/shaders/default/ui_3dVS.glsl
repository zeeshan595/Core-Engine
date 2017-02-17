#version 450

in vec3 vertex_position_model;
in vec4 vertex_color;
in vec2 vertex_uv;
in vec3 vertex_normal_model;

out vec2 the_uv;

uniform mat4 mvp_matrix;

void main()
{
    the_uv = vertex_uv;

    vec4 v = vec4(vertex_position_model, 1.0f);
    gl_Position = mvp_matrix * v;
}