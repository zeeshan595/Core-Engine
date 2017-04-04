#version 330

in vec3 vertexPosition;

// uniform mat4 MVP;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexTexCoords;


void main()
{
	vertexTexCoords = vertexPosition;

	vec4 MVP = projection * view * vec4(vertexPosition, 1.0f);
	gl_Position = MVP;
}
