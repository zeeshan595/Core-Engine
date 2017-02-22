#version 150

//the output Frag Colour
out vec4 FragColor;
in vec4 vertexColourOut;
//The main function
void main()
{
  //The frag colour
  FragColor = vertexColourOut;
}
