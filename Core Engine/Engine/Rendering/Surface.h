#ifndef _SURFACE
#define _SURFACE

#include "Texture.h"

class Surface
{
public:
    enum SHADER_TYPE
    {
        VERTEX_SHADER = GL_VERTEX_SHADER,
        FRAGMENT_SHADER = GL_FRAGMENT_SHADER
    };

    Surface(std::string vertex_shader_path, std::string fragment_shader_path);
    ~Surface();
    void ApplyTexture(std::shared_ptr<Texture> tex);

    GLuint GetShaderProgram(){
        return shader_program;
    }
    std::shared_ptr<Texture> GetTexture(){
        return texture;
    }

private:
    GLuint shader_program;
    std::shared_ptr<Texture> texture;

    GLuint LoadShaderFromMemory(const char * pMem, SHADER_TYPE shader_type);
    GLuint LoadShaderFromFile(const std::string& filename, SHADER_TYPE shader_type);
    bool CheckForCompilerErrors(GLuint shader_program);
    bool CheckForLinkErrors(GLuint program);

};

#include "Surface.cpp"

#endif