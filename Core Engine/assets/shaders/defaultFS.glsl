#version 150

out vec4 FragColor;

//uniform vec3 lightPosition;
//uniform sampler2D texture0;

void main()
{
    //vec3 lightVector = normalize(lightPosition - vertexPositionOut);
    //float brightness = dot(lightVector, vertexNormalsOut) * 20;
    //vec4 textureColor = texture(texture0, vertexTexCoordsOut);
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}