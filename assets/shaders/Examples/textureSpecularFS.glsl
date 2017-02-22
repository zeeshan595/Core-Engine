#version 150

out vec4 FragColor;
in vec3 worldNormal;
in vec3 cameraDirectionOut;
in vec2 vertexTexCoordsOut;

uniform vec3 lightDirection;

uniform vec4 ambientMaterialColour;
uniform vec4 diffuseMaterialColour;
uniform vec4 specularMaterialColour;
uniform float specularPower;

uniform vec4 ambientLightColour;
uniform vec4 diffuseLightColour;
uniform vec4 specularLightColour;
uniform	sampler2D texture0;

void main()
{
	vec3 lightDirectionNormalized=normalize(lightDirection);
	float diffuseTerm = max(dot(worldNormal, lightDirectionNormalized),0.0f);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDirectionNormalized);
	float specularTerm = pow(max(dot(worldNormal, halfWayVec),0.0f), specularPower);

	FragColor = (ambientMaterialColour*ambientLightColour) +
	(diffuseMaterialColour*diffuseLightColour*diffuseTerm) +
	(specularMaterialColour*specularLightColour*specularTerm);

	FragColor = FragColor * texture(texture0,	vertexTexCoordsOut);
}
