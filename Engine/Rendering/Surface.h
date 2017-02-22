#ifndef _SURFACE
#define _SURFACE

//0 = color map
//1 = normal map
//2 = specular map
class Surface
{
public:
    Surface(std::shared_ptr<Shader> shader);
    std::shared_ptr<Shader> GetShader();
    std::vector<std::shared_ptr<Texture>>* GetTextures();
    void SetColorMap(std::shared_ptr<Texture> texture);
    void SetNormalMap(std::shared_ptr<Texture> texture);
    void SetSpecularMap(std::shared_ptr<Texture> texture);
    void AddAdditionalTexture(std::shared_ptr<Texture> texture);
    static std::shared_ptr<Surface> LoadDefaultSurface();

private:
    std::shared_ptr<Shader> shader;
    std::vector<std::shared_ptr<Texture>> textures;
};

#include "Surface.c"

#endif