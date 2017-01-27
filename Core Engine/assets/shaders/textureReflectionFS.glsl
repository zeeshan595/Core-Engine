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
uniform samplerCube cubeTexture;

void main()
{
	vec3 lightDirectionNormalized=normalize(lightDirection);
	float diffuseTerm = max(dot(worldNormal, lightDirectionNormalized),0.0f);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDirectionNormalized);
	float specularTerm = pow(max(dot(worldNormal, halfWayVec),0.0f), specularPower);

	vec3 reflected = reflect(normalize(worldNormal), normalize(cameraDirectionOut));
	vec4 reflectionColour = texture(cubeTexture, normalize(reflected));

	vec4 materialColor = (ambientMaterialColour*ambientLightColour) +
	(diffuseMaterialColour*diffuseLightColour*diffuseTerm) +
	(specularMaterialColour*specularLightColour*specularTerm);

	materialColor = materialColor * texture(texture0,	vertexTexCoordsOut);

	FragColor = mix(materialColor,reflectionColour,0.5f);

}
