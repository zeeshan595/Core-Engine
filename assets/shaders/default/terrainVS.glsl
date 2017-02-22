#version 150

in vec3 vertex_position_model;
in vec4 vertex_color;
in vec2 vertex_uv;
in vec3 vertex_normal_model;

out vec3 vertex_position_world;
out vec4 the_color;
out vec2 the_uv;
out vec3 vertex_normal_world;

uniform mat4 model_view_projection_matrix;
uniform mat4 model_to_world_matrix;

void main()
{
    the_color = vertex_color;
    the_uv = vertex_uv;

    vec4 v = vec4(vertex_position_model, 1.0f);

    vertex_normal_world = vec3(model_to_world_matrix * vec4(vertex_normal_model, 0.0f));
    vertex_position_world = vec3(model_to_world_matrix * v);
    gl_Position = model_view_projection_matrix * v;
}