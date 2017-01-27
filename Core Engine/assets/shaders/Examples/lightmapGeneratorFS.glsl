#version 150

out vec4 FragColor;

void main()
{
	//This shouldn't be used in basic shadow map generation
	FragColor = vec4(gl_FragCoord.z);
}
