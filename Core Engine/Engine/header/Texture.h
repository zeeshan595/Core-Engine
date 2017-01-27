#ifndef _TEXTURE
#define _TEXTURE

class Texture
{
public:
    Texture(const std::string& filename);
    ~Texture();

    GLuint GetTextureMap(){
        return texture_map;
    }

private:
    GLuint texture_map;
    GLuint ConvertSDLSurfaceToTexture(SDL_Surface* surface);
};

#include "../src/Texture.cpp"

#endif