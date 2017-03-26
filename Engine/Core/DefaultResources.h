#ifndef _DEFAULT_RESOURCES
#define _DEFAULT_RESOURCES

class DefaultResources
{
public:
    static void CreateDefaultResources();
    static void DestroyDefaultResources();

    static const GLuint         GetCubeVAO();
    static const GLuint         GetCubeVBO();
    static const GLuint         GetCubeEBO();

    static const GLuint         GetPlaneVAO();
    static const GLuint         GetPlaneVBO();
    static const GLuint         GetPlaneEBO();

private:

    static GLuint       plane_VAO;
    static GLuint       plane_VBO;
    static GLuint       plane_EBO;

    static GLuint       cube_VAO;
    static GLuint       cube_VBO;
    static GLuint       cube_EBO;
};

#include "DefaultResources.cpp"
#endif