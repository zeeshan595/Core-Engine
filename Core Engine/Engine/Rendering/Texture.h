#ifndef _TEXTURE
#define _TEXTURE

class Texture
{
public:
    Texture(int width, int height, bool is_depth = false);
    Texture(const std::string& filename);
    ~Texture();

    static SDL_Surface* LoadImage(const std::string& filename){
        //Use SDL surface to load texture from a file.
        SDL_Surface* image_surface = IMG_Load((TEXTURE_PATH + filename).c_str());
        if (!image_surface)
        {
            std::cout << "ERROR [IMG_Load]: " << filename << " - " << IMG_GetError();
            return nullptr;
        }
        return image_surface;
    }


    GLuint GetTextureMap(){
        return texture_map;
    }

private:
    GLuint texture_map;
    GLuint ConvertSDLSurfaceToTexture(SDL_Surface* surface);
};

#include "Texture.cpp"

#endif