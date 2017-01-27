#version 150

out vec4 FragColor;

in vec2 vertexTexCoordsOut;

uniform	sampler2D texture0;
uniform vec4 textColour;

void main()
{
  FragColor = texture(texture0,	vertexTexCoordsOut)*textColour;
}
