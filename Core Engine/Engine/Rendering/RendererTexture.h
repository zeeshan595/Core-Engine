#ifndef _RENDERER_TEXTURE
#define _RENDERER_TEXTURE

#include "Texture.h"

class RendererTexture
{
public:
    RendererTexture(int width, int height)
    {

    }

private:
    GLint FBO;
    std::shared_ptr<Texture> texture;
    int width;
    int height;

    void CreateFBO()
    {
        texture = std::shared_ptr<Texture>(new Texture(width, height));
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    }
};

#endif