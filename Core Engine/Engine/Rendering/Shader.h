#ifndef _SHADER
#define _SHADER

class Shader
{
public:
    enum SHADER_TYPE{
        VERTEX_SHADER = GL_VERTEX_SHADER,
        FRAGMENT_SHADER = GL_FRAGMENT_SHADER
    };

    Shader(std::string vertex_shader_path, std::string fragment_shader_path);
    ~Shader();

    GLuint GetShaderProgram();
private:
    GLuint shader_program;

    GLuint LoadShaderFromMemory(const char * pMem, SHADER_TYPE shader_type);
    GLuint LoadShaderFromFile(const std::string& filename, SHADER_TYPE shader_type);
    bool CheckForCompilerErrors(GLuint shader_program);
    bool CheckForLinkErrors(GLuint program);
};

#include "Shader.cpp"

#endif