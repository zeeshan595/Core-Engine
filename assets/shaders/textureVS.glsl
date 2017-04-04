#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoords;
out vec2 vertexTextCoordsOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat4 MVP = projection * view * model;
    gl_Position = MVP * vec4(vertexPosition, 1.0f);
    vertexTextCoordsOut = vertexTexCoords;
}