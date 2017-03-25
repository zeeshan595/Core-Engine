#ifndef _SHADER
#define _SHADER

class Shader
{
public:
    enum SHADER_TYPE{
        VERTEX_SHADER = GL_VERTEX_SHADER,
        GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
        FRAGMENT_SHADER = GL_FRAGMENT_SHADER
    };

    Shader(const char* vertex_shader_path, const char* fragment_shader_path);
    ~Shader();

    const GLuint GetShaderProgram();

private:
    GLuint LoadShaderFromMemory(const char* memory, SHADER_TYPE shader_type);
    GLuint LoadShaderFromFile(const char* filename, SHADER_TYPE shader_type);
    bool CheckForCompilerErrors(GLuint shader_program);
    bool CheckForLinkErrors(GLuint program);

    GLuint          shader_program          = 0;

};

#include "Shader.cpp"
#endif