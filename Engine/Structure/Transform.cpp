Transform::Transform()
{
    position        = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation        = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    size            = glm::vec3(1.0f, 1.0f, 1.0f);
    model_matrix    = glm::mat4x4(1.0f);
}

void Transform::ConstructMatrix()
{
    glm::mat4x4 pos = glm::translate(glm::mat4x4(1.0f), position);
    glm::mat4x4 rot = glm::toMat4(rotation);
    glm::mat4x4 sca = glm::scale(glm::mat4x4(1.0f), size);
    model_matrix = pos * rot * sca;
}

void Transform::SetPosition    (glm::vec3 t)
{
    position = t;
    ConstructMatrix();
}
void Transform::Rotate         (glm::vec3 r)
{
    glm::quat qPitch    = glm::angleAxis(r.x, glm::vec3(1, 0, 0));
    glm::quat qYaw      = glm::angleAxis(r.y, glm::vec3(0, 1, 0));
    glm::quat qRoll     = glm::angleAxis(r.z, glm::vec3(0, 0, 1));
    rotation            = qYaw *qPitch * qRoll;
    ConstructMatrix();
}
void Transform::SetRotation    (glm::quat q)
{
    rotation = q;
    ConstructMatrix();
}
void Transform::SetSize        (glm::vec3 s)
{
    size = s;
    ConstructMatrix();
}

void Transform::SetWorldMatrix (glm::mat4x4 mat)
{
    glm::mat4x4 sca = glm::scale(glm::mat4x4(1.0f), size);
    model_matrix = sca * mat;
    position = glm::vec3(model_matrix[3][0], model_matrix[3][1], model_matrix[3][2]);
    rotation = glm::quat(model_matrix);
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

glm::mat4x4     Transform::GetMatrix()
{
    return model_matrix;
}
glm::vec3       Transform::EulerAngles()
{
    return glm::eulerAngles(rotation);
}
glm::vec3       Transform::Forward()
{
    return glm::vec3(model_matrix[2][0], model_matrix[2][1], model_matrix[2][2]);
}
glm::vec3       Transform::Up()
{
    return glm::vec3(model_matrix[1][0], model_matrix[1][1], model_matrix[1][2]);
}
glm::vec3       Transform::Right()
{
    return glm::vec3(model_matrix[0][0], model_matrix[0][1], model_matrix[0][2]);
}