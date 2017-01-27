#version 150

out vec4 FragColor;
in vec2 textureCoords;

uniform sampler2D texture0;
uniform mat3 colourFilter = mat3(1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0);

void main()
{

	vec3 textureColour=texture(texture0, textureCoords).rgb;
	textureColour=textureColour*colourFilter;
	FragColor=vec4(textureColour,1.0f);
}