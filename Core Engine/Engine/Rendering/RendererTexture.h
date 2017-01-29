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

private:
    unsigned int FBO;
    std::shared_ptr<Texture> texture;
    int width;
    int height;

    void CreateFBO()
    {
        texture = std::shared_ptr<Texture>(new Texture(width, height));
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        //GL_COLOR_ATTACHMENT0 OR GL_DEPTH_ATTACHMENT 
        //To define what you want to render to the texture
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->GetTextureMap(), 0);
        //Set the current framebuffer to zero so we use defualt one
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};

#endif