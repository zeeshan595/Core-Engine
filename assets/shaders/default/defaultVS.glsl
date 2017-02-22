#version 150

in vec3 vertex_position_model;
in vec4 vertex_color;
in vec2 vertex_uv;
in vec3 vertex_normal_model;
in vec3 tangent;

out vec3 vertex_position_world;
out vec4 the_color;
out vec2 the_uv;
out mat3 tangent_to_world_matrix;

uniform mat4 model_view_projection_matrix;
uniform mat4 model_to_world_matrix;

void main()
{
    vec4 v = vec4(vertex_position_model, 1.0f);

    the_color = vertex_color;
    the_uv = vertex_uv;
    vertex_position_world = vec3(model_to_world_matrix * v);

    vec3 n = normalize( ( model_to_world_matrix * vec4( vertex_normal_model, 0.0 ) ).xyz );
    vec3 t = normalize( ( model_to_world_matrix * vec4( tangent.xyz, 0.0 ) ).xyz );
    vec3 b = normalize( ( model_to_world_matrix * vec4( ( cross( vertex_normal_model, tangent.xyz ) ), 0.0 ) ).xyz );
    tangent_to_world_matrix = mat3( t, b, n );

    gl_Position = model_view_projection_matrix * v;
}