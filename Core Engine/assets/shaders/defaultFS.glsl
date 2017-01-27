#version 150

out vec4 FragColor;

in vec3 the_vertex_position;
in vec2 the_vertex_uv;
in vec3 the_vertex_normal;

uniform vec3 lightPosition;
uniform sampler2D texture0;

void main()
{
    //vec3 lightVector = normalize(lightPosition - the_vertex_position);
    //float brightness = dot(lightVector, the_vertex_normal) * 20;
    FragColor = texture(texture0, the_vertex_uv);
}