#version 150

in vec3 vertex_position_model;

out vec3 the_uv;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;

void main()
{
    the_uv = vertex_position_model;

    vec4 v = vec4(vertex_position_model, 1.0f);
    gl_Position = projection_matrix * view_matrix * v;
}