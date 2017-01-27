#version 150

out vec4 FragColor;

in vec4 vertexColourOut;
uniform vec4 ambientMaterialColour;
uniform vec4 ambientLightColour;

void main()
{
	FragColor = ambientMaterialColour*ambientLightColour;
}
