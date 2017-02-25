Transform::Transform()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    model_matrix = glm::mat4x4(1.0f);
}

void Transform::Translate(glm::vec3 t)
{
    position = t;
    BuildModelMatrix();
}
void Transform::Rotate(glm::vec3 r)
{
    glm::quat qPitch = glm::angleAxis(r.x, glm::vec3(1, 0, 0));
    glm::quat qYaw   = glm::angleAxis(r.y, glm::vec3(0, 1, 0));
    glm::quat qRoll  = glm::angleAxis(r.z, glm::vec3(0, 0, 1));
    rotation = qYaw *qPitch * qRoll;
    BuildModelMatrix();
}
void Transform::SetRotation(glm::quat q)
{
    rotation = q;
}
void Transform::Scale(glm::vec3 s)
{
    size = s;
    BuildModelMatrix();
}

glm::vec3 Transform::GetPosition()
{
    return position;
}
glm::quat Transform::GetRotation()
{
    return rotation;
}
glm::vec3 Transform::GetSize()
{
    return size;
}

glm::mat4x4 Transform::GetWorldMatrix()
{
    return model_matrix;
}
glm::vec3 Transform::EulerAngles()
{
    return glm::eulerAngles(rotation);
}
glm::vec3 Transform::Forward()
{
    return glm::vec3(GetWorldMatrix()[2][0], GetWorldMatrix()[2][1], GetWorldMatrix()[2][2]);
}
glm::vec3 Transform::Up()
{
    return glm::vec3(GetWorldMatrix()[1][0], GetWorldMatrix()[1][1], GetWorldMatrix()[1][2]);
}
glm::vec3 Transform::Right()
{
    return glm::vec3(GetWorldMatrix()[0][0], GetWorldMatrix()[0][1], GetWorldMatrix()[0][2]);
}

float Transform::ToRadians(float d)
{
    return (d / 180.0f) * glm::pi<float>();
}

float Transform::ToDegrees(float r)
{
    return (r / glm::pi<float>()) * 180.0f;
}

void Transform::BuildModelMatrix()
{
    glm::mat4x4 pos = glm::translate(glm::mat4x4(1.0f), position);
    glm::mat4x4 rot = glm::toMat4(rotation);
    glm::mat4x4 sca = glm::scale(glm::mat4x4(1.0f), size);
    model_matrix = pos * rot * sca;
}