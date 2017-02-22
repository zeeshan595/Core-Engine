#ifndef _RAYCAST
#define _RAYCAST

class Raycast
{
public:
    static glm::vec3 GetRay(glm::vec2 point){
        int selected_camera = -1;
        std::vector<std::shared_ptr<Camera>>* cameras = Environment::GetCameras();
        for (int i = 0; i < (*cameras).size() && selected_camera == -1; i++)
        {
            if (point.x >= (*cameras)[i]->viewport.x * Screen::width && point.x < (*cameras)[i]->viewport.z * Screen::width && point.y > (*cameras)[i]->viewport.y * Screen::height && point.y < (*cameras)[i]->viewport.w * Screen::height)
            {
                selected_camera = i;
            }
        }
        if (selected_camera == -1)
            return glm::vec3(0.0f, 0.0f, 0.0f);

        std::shared_ptr<Camera> cam = (*cameras)[selected_camera];

        glm::vec2 normalizedDeviceSpace = NormalisedDeviceSpace(point);
        glm::vec4 homogeneousClipSpace = glm::vec4(normalizedDeviceSpace.x, normalizedDeviceSpace.y, -1.0f, 1.0f);
        glm::vec4 eyeSpace = EyeSpace(cam, homogeneousClipSpace);
        return WorldSpace(cam, eyeSpace);
    }

private:
    static glm::vec2 NormalisedDeviceSpace(glm::vec2 point){
        float x = (2.0f * point.x) / Screen::width - 1.0f;
        float y = (2.0f * point.y) / Screen::height - 1.0f;
        return glm::vec2(x, -y);
    }
    static glm::vec4 EyeSpace(std::shared_ptr<Camera> camera, glm::vec4 point){
        glm::mat4x4 invertedProjection = glm::inverse(camera->GetProjectionMatrix());
        glm::vec4 eyeSpace = point * invertedProjection;
        return glm::vec4(eyeSpace.x, eyeSpace.y, -1.0f, 0.0f);
    }
    static glm::vec3 WorldSpace(std::shared_ptr<Camera> camera, glm::vec4 point){
        glm::mat4x4 invertedView = glm::inverse(camera->GetViewMatrix());
        glm::vec4 worldSpace = point * invertedView;
        glm::vec3 ray = glm::vec3(worldSpace.x, worldSpace.y, worldSpace.z);
        ray = glm::normalize(ray);
        return ray;
    }
};

#endif