#ifndef _MATERIAL
#define _MATERIAL

class Material
{
public:
    Material();
    ~Material();

    void SetShader(Shader* shader);
    void SetColorMap(Texture* texture);
    void SetNormalMap(Texture* texture);
    void SetTextures(std::vector<Texture*> textures);
    Shader*                   GetShader();
    std::vector<Texture*>*    GetTextures();

    float       GetShineDamper();
    float       GetLightReflectivity();

    void        SetShineDamper(float v);
    void        SetLightReflectivity(float v);

private:
    Shader*                         shader                  = NULL;
    std::vector<Texture*>           textures;
    float                           light_reflectivity      = 1.0f;
    float                           shine_damper            = 10.0f;

};

#include "Material.cpp"
#endif