#version 150

in vec3 vertex_position_model;
in vec4 vertex_color;
in vec2 vertex_uv;
in vec3 vertex_normal_model;

out vec3 the_position_model;
out vec4 the_color;
out vec2 the_uv;
out vec3 the_normal_model;

uniform mat4 model_view_projection_matrix;

void main()
{
    the_color = vertex_color;
    the_uv = vertex_uv;
    the_normal_model = vertex_normal_model;
    the_position_model = vertex_position_model;

    vec4 v = vec4(vertex_position_model, 1.0f);
    gl_Position = model_view_projection_matrix * v;
}