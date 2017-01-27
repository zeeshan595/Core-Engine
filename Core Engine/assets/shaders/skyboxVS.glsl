#version 330
layout (location=0) in vec3 position;
out vec3 Texcoords;

uniform mat4 projMat;
uniform mat4 viewMat;

void main()
{
	gl_Position=projMat*viewMat*vec4(position, 1.0);
	TexCoords=position;
}