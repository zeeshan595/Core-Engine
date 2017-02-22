#version 150

in vec3 vertex_position_model;
in vec2 vertex_uv;

out vec2 the_uv;

uniform mat4 model_view_projection_matrix;

void main()
{
    the_uv = vertex_uv;

    vec4 v = vec4(vertex_position_model, 1.0f);
    gl_Position = model_view_projection_matrix * v;
}