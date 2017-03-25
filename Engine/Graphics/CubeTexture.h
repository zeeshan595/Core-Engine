#ifndef _CUBE_TEXTURE
#define _CUBE_TEXTURE

class CubeTexture
{
public:
    CubeTexture(const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ);
    ~CubeTexture();

    GLuint GetTextureMap();

private:
    void LoadCubeMapFace(const std::string& filename, GLenum face);

    GLuint          cube_texture            = 0;
};

#include "CubeTexture.cpp"
#endif