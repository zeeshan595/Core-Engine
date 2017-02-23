#ifndef _TRANSFORM
#define _TRANSFORM

class Transform
{
public:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    Transform(){
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    void Translate(glm::vec3 t){
        position += t;
    }

    glm::mat4x4 GetWorldMatrix(){
        glm::mat4x4 pos = glm::translate(glm::mat4x4(1.0f), position);

        glm::mat4x4 rot = glm::toMat4(rotation);

        glm::mat4x4 sca = glm::scale(glm::mat4x4(1.0f), scale);

        return pos * rot * sca;
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

    void Rotate(glm::vec3 amount){
        glm::vec3 euler  = amount;
        glm::quat qPitch = glm::angleAxis(euler.x, glm::vec3(1, 0, 0));
        glm::quat qYaw   = glm::angleAxis(euler.y, glm::vec3(0, 1, 0));
        glm::quat qRoll  = glm::angleAxis(euler.z, glm::vec3(0, 0, 1));

        ///x,y,z are in radians
        rotation = qYaw *qPitch * qRoll;
    }
    glm::vec3 EulerAngles(){
        return glm::eulerAngles(rotation);
    }

	static float ToRadians(float d){
		return (d / 180.0f) * glm::pi<float>();
	}

	static float ToDegrees(float r){
		return (r / glm::pi<float>()) * 180.0f;
	}
};

#endif