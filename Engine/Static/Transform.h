#ifndef _TRANSFORM
#define _TRANSFORM

class Transform
{
public:
    Transform();

    void Translate(glm::vec3 t);
    void Rotate(glm::vec3 r);
    void SetRotation(glm::quat q);
    void Scale(glm::vec3 s);

    glm::vec3 GetPosition();
    glm::quat GetRotation();
    glm::vec3 GetSize();

    glm::mat4x4 GetWorldMatrix();
    glm::vec3 EulerAngles();
    glm::vec3 Forward();
    glm::vec3 Up();
    glm::vec3 Right();

	static float ToRadians(float d);
	static float ToDegrees(float r);

private:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 size;
    glm::mat4x4 model_matrix;

    void BuildModelMatrix();
};

#include "Transform.c"

#endif