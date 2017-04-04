#version 330

in vec3 vertexTexCoords;

out vec4 FragColor;

uniform samplerCube cubeTexture;

void main()
{
	vec4 cubeMapColor =  texture(cubeTexture, vertexTexCoords);
	FragColor = cubeMapColor;
}
