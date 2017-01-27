#version 150

in vec3 vertex_position;
in vec2 vertex_uv;
in vec3 vertex_normal;

out vec3 vertex_position_out;
out vec2 vertex_uv_out;
out vec3 vertex_normal_out;

uniform mat4 MVP;

void main()
{
    vertex_position_out = vertex_position;
    gl_Position = MVP * vec4(vertex_position, 1.0f);
}