#ifndef _TRANSFORM
#define _TRANSFORM

class Transform
{
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform()
    {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    void Translate(glm::vec3 t)
    {
        position += t;
    }

    glm::mat4x4 GetWorldMatrix()
    {
        glm::mat4x4 scale_matrix = glm::scale(glm::mat4x4(1.0f), scale);

        glm::mat4x4 rotation_matrix = glm::mat4x4(1.0f);
        rotation_matrix = glm::rotate(rotation_matrix, ToRadians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        rotation_matrix = glm::rotate(rotation_matrix, ToRadians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotation_matrix = glm::rotate(rotation_matrix, ToRadians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4x4 position_matrix = glm::translate(glm::mat4x4(1.0f), position);

        return scale_matrix * rotation_matrix * position_matrix;
    }

    glm::vec3 Forward()
    {
        return glm::vec3(GetWorldMatrix()[2][0], GetWorldMatrix()[2][1], GetWorldMatrix()[2][2]);
    }
    glm::vec3 Up()
    {
        return glm::vec3(GetWorldMatrix()[1][0], GetWorldMatrix()[1][1], GetWorldMatrix()[1][2]);
    }
private:
	float ToRadians(float d)
	{
		return (d / 180.0f) * glm::pi<float>();
	}

	float ToDegrees(float r)
	{
		return (r / glm::pi<float>()) * 180.0f;
	}
};

#endif