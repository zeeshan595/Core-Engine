#version 150

//The input vertex
in vec3 vertexPosition;
in vec4 vertexColour;

out vec4 vertexColourOut;

//The MVP matrix
uniform mat4 MVP;

//The main function
void main()
{
  //Calculate the transformed position
  vertexColourOut=vertexColour;
  gl_Position = MVP * vec4(vertexPosition, 1.0);
}
