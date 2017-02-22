#version 150

in vec3 vertex_position_model;

out vec2 the_uv;

uniform mat4 ui_transformation;

void main()
{
    the_uv = vec2(vertex_position_model.x, 1.0f - vertex_position_model.y);

    vec4 v = vec4(vertex_position_model, 1.0f);
    gl_Position = ui_transformation * v;
}