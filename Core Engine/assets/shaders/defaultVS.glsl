#version 150

in vec3 vertexPosition;



in vec3 vertexABCDEF;
in vec3 vertexTexCoords;

uniform mat4 MVP;

void main()
{
    vec3 test = vertexTexCoords;
    gl_Position = MVP * vec4(vertexPosition, 1.0f);
}