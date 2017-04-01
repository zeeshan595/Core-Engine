#version 150

in vec3 vertex_position;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 transform_matrix;

void main()
{
    gl_Position = projection_matrix * view_matrix * transform_matrix * vec4(vertex_position, 1.0f);
}