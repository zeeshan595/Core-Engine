#version 150

out vec4 FragColor;
in vec3 vertexTexCoords;

uniform samplerCube cubeTexture;

void main()
{
	FragColor = texture(cubeTexture, vertexTexCoords);
	//FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}
