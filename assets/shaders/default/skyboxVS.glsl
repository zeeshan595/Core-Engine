#version 150

in vec3 vertex_position;

out vec3 the_uv;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;

void main()
{
    the_uv = vertex_position;

    vec4 v = vec4(vertex_position, 1.0f);
    gl_Position = projection_matrix * view_matrix * v;
}