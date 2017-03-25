#ifndef _DEFAULT_RESOURCES
#define _DEFAULT_RESOURCES

class DefaultResources
{
public:
    void CreateDefaultResources();
    void DestroyDefaultResources();

    const GLuint        GetCubeVAO();
    const GLuint        GetCubeVBO();
    const GLuint        GetCubeEBO();

    const GLuint        GetPlaneVAO();
    const GLuint        GetPlaneVBO();
    const GLuint        GetPlaneEBO();

private:

    GLuint      plane_VAO        = 0;
    GLuint      plane_VBO        = 0;
    GLuint      plane_EBO        = 0;

    GLuint      cube_VAO        = 0;
    GLuint      cube_VBO        = 0;
    GLuint      cube_EBO        = 0;

};

#endif