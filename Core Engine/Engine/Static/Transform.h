#ifndef _TRANSFORM
#define _TRANSFORM

class Transform
{
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform(){
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    void Translate(glm::vec3 t){
        position += t;
    }

    glm::mat4x4 GetWorldMatrix(){
        glm::mat4x4 model_matrix = glm::mat4x4(1.0f);

        model_matrix = glm::translate(model_matrix, position);

        model_matrix = glm::rotate(model_matrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        model_matrix = glm::rotate(model_matrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model_matrix = glm::rotate(model_matrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

        model_matrix = glm::scale(model_matrix, scale);

        return model_matrix;
    }

    glm::vec3 Forward(){
        return glm::vec3(GetWorldMatrix()[2][0], GetWorldMatrix()[2][1], GetWorldMatrix()[2][2]);
    }
    glm::vec3 Up(){
        return glm::vec3(GetWorldMatrix()[1][0], GetWorldMatrix()[1][1], GetWorldMatrix()[1][2]);
    }
    glm::vec3 Right(){
        return glm::vec3(GetWorldMatrix()[0][0], GetWorldMatrix()[0][1], GetWorldMatrix()[0][2]);
    }

	static float ToRadians(float d){
		return (d / 180.0f) * glm::pi<float>();
	}

	static float ToDegrees(float r){
		return (r / glm::pi<float>()) * 180.0f;
	}
};

#endif