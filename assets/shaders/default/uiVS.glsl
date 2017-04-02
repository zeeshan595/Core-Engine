#version 150

in vec3 vertex_position;
out vec2 the_uv;

uniform mat4 transform_matrix;

void main()
{
    the_uv = vec2(vertex_position.x, 1.0f - vertex_position.y);

    vec4 v = vec4(vertex_position, 1.0f);
    gl_Position = transform_matrix * v;
}