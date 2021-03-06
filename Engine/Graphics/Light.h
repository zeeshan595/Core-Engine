#ifndef _LIGHT
#define _LIGHT

class Light : public Entity
{
public:
    enum LIGHT_TYPE{
        POINT = 0,
        DIRECTIONAL = 1
    };

    Light(const char* name);

    void SetLightType(LIGHT_TYPE type);
    void SetLightColor(float r, float g, float b);
    void SetLightBrightness(float brightness);
    void SetPointLightRange(float range);

    LIGHT_TYPE          GetLightType();
    glm::vec3           GetLightColor();
    float               GetLightBrightness();
    float               GetPointLightRange();

private:
    LIGHT_TYPE          type;
    glm::vec3           color;
    float               brightness;
    float               light_range;

};

#include "Light.cpp"
#endif