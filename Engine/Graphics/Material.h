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

private:
    Shader*                         shader          = NULL;
    std::vector<Texture*>           textures;

};

#include "Material.cpp"
#endif