#ifndef _LIGHT
#define _LIGHT

#include "Transform.h"

class Light
{
public:
    enum LIGHT_TYPE{
        POINT = 0,
        DIRECTIONAL = 1
    };

    glm::vec4 color;
    float brightness;
    Transform transform;
    LIGHT_TYPE light_type;

    Light(LIGHT_TYPE type)
    {
        color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        brightness = 1.0f;
        transform = Transform();
        light_type = type;
    }
};

#endif