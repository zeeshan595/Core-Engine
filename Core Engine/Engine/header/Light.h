#ifndef _LIGHT
#define _LIGHT

#include "Transform.h"

class Light
{
public:
    enum LIGHT_TYPE{
        AMBIENT = 0,
        POINT = 1,
        DIRECTIONAL = 2
    };

    std::vec4 color;
    float brightness;
    Transform transform;

    Light()
    {
        color = std::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        brightness = 1.0f;
        transform = Transform();
    }
};

#endif