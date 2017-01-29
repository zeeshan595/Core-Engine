#ifndef _RENDERER_TEXTURE
#define _RENDERER_TEXTURE

#include "Texture.h"

class RendererTexture
{
public:
    RendererTexture(int w, int h)
    {
        width = w;
        height = h;
        CreateFBO();
    }
    unsigned int GetFBO(){
        return FBO;
    }
    std::shared_ptr<Texture> GetTexture(){
        return texture_map;
    }

private:
    unsigned int FBO;
    std::shared_ptr<Texture> texture_map;
    std::shared_ptr<Texture> texture_depth;
    int width;
    int height;

    void CreateFBO()
    {
        texture_map = std::shared_ptr<Texture>(new Texture(width, height));
        texture_depth = std::shared_ptr<Texture>(new Texture(width, height, true));
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_map->GetTextureMap(), 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture_depth->GetTextureMap(), 0);
        //Set the current framebuffer to zero so we use defualt one
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};

#endif