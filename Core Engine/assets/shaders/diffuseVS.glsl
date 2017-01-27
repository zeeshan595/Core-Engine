#version 150

in vec3 vertexPosition;
in vec3 vertexNormal;

out vec3 worldNormal;

uniform mat4 MVP;
uniform mat4 Model;

void main()
{
	worldNormal = normalize(Model*vec4(vertexNormal,0.0f)).xyz;
	gl_Position = MVP * vec4(vertexPosition, 1.0);
}
