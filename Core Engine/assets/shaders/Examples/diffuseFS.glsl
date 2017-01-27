#version 150

out vec4 FragColor;

in vec3 worldNormal;

uniform vec3 lightDirection;

uniform vec4 ambientMaterialColour;
uniform vec4 diffuseMaterialColour;

uniform vec4 ambientLightColour;
uniform vec4 diffuseLightColour;

void main()
{
	float diffuseTerm = dot(worldNormal, lightDirection);
	FragColor = (ambientMaterialColour*ambientLightColour)+(diffuseMaterialColour*diffuseLightColour*diffuseTerm);
}
