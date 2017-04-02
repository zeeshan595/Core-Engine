#ifndef _TRANSFORM
#define _TRANSFORM

class Transform
{
public:
    Transform();

    void SetPosition    (glm::vec3 t);
    void Rotate         (glm::vec3 r);
    void SetRotation    (glm::quat q);
    void SetSize        (glm::vec3 s);
    void SetWorldMatrix (glm::mat4x4 mat);

    glm::vec3 GetPosition();
    glm::quat GetRotation();
    glm::vec3 GetSize();

    glm::mat4x4     GetMatrix();
    glm::vec3       EulerAngles();
    glm::vec3       Forward();
    glm::vec3       Up();
    glm::vec3       Right();

private:
    glm::vec3               position;
    glm::quat               rotation;
    glm::vec3               size;
    glm::mat4x4             model_matrix;

    void ConstructMatrix();
};

#include "Transform.cpp"
#endif