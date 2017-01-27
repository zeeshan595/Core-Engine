#version 150

in vec3 vertex_position;
in vec2 vertex_uv;
in vec3 vertex_normal;

out vec3 the_vertex_position;
out vec2 the_vertex_uv;
out vec3 the_vertex_normal;

uniform mat4 MVP;

void main()
{
    the_vertex_position = vertex_position;
    the_vertex_uv = vertex_uv;
    //the_vertex_normal = vertex_normal;
    gl_Position = MVP * vec4(vertex_position, 1.0f);
}