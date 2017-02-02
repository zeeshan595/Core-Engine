#ifndef _FOG
#define _FOG

class Fog
{
public:
    static float distance;
    static float density;
    static float gradient;
    static glm::vec4 fog_color;
};
float Fog::distance = 5.0f;
float Fog::density  = 0.007f;
float Fog::gradient = 1.5f;
glm::vec4 Fog::fog_color = glm::vec4(0.7f, 0.7f, 0.75f, 1.0f);

#endif