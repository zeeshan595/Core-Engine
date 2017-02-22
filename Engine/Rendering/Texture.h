#ifndef _TEXTURE
#define _TEXTURE

class Texture
{
public:
    Texture(int width, int height, bool is_depth = false);
    Texture(const std::string& filename);
    ~Texture();
    void ApplyTextureFilter();
    GLuint GetTextureMap();

    static std::shared_ptr<Texture> LoadDefaultTexture();
    static SDL_Surface* LoadImage(const std::string& filename);

private:
    GLuint texture_map;
    GLuint ConvertSDLSurfaceToTexture(SDL_Surface* surface);
};

#include "Texture.c"

#endif