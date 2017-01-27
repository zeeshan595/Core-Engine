#version 150

in vec2 vertexPosition;
out vec2 textureCoords;

void main()
{
	textureCoords = (vertexPosition + 1.0) / 2.0;
	gl_Position = vec4(vertexPosition,0.0, 1.0);
}