#ifndef _TEXTURE
#define _TEXTURE

class Texture
{
public:
    Texture(const char* filename);
    ~Texture();

    const GLuint GetTextureMap();

private:
    GLuint          texture_map         = 0;
    
    void ApplyImageFilter();
    GLuint ConvertSDLSurfaceToTexture(SDL_Surface* surface);
    SDL_Surface* LoadImageFromFile(const char* filename);
};

#include "Texture.cpp"
#endif