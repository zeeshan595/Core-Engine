Light::Light(const char* name) : Entity(name)
{
    type            = LIGHT_TYPE::POINT;
    color           = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    brightness      = 1.0f;
    light_range     = 20.0f;
}

void Light::SetLightType(LIGHT_TYPE type)
{
    this->type = type;
}
void Light::SetLightColor(float r, float g, float b, float a)
{
    this->color = glm::vec4(r, g, b, a);
}
void Light::SetLightBrightness(float brightness)
{
    this->brightness = brightness;
}
void Light::SetPointLightRange(float range)
{
    this->light_range = range;
}

Light::LIGHT_TYPE   Light::GetLightType()
{
    return type;
}
glm::vec4           Light::GetLightColor()
{
    return color;
}
float               Light::GetLightBrightness()
{
    return brightness;
}
float               Light::GetPointLightRange()
{
    return light_range;
}