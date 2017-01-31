#include "Engine/Core/Core.h"

class cameraMovment : public Module
{
public:
    void Update()
    {
        if (Input::keys[SDLK_a])
        {
            attached_to->transform.position += glm::vec3(1.0f, 0.0f, 0.0f) * Time::delta_time;
        }
        if (Input::keys[SDLK_d])
        {
            attached_to->transform.position -= glm::vec3(1.0f, 0.0f, 0.0f) * Time::delta_time;
        }
        if (Input::keys[SDLK_w])
        {
            attached_to->transform.position += glm::vec3(0.0f, 0.0f, 1.0f) * Time::delta_time;
        }
        if (Input::keys[SDLK_s])
        {
            attached_to->transform.position -= glm::vec3(0.0f, 0.0f, 1.0f) * Time::delta_time;
        }
    }
};

class modelRotator : public Module
{
public:
    void Update()
    {
        if (Input::keys[SDLK_l])
        {
            attached_to->transform.rotation += glm::vec3(0.0f, 25.0f, 0.0f) * Time::delta_time;
        }
        if (Input::keys[SDLK_k])
        {
            attached_to->transform.rotation -= glm::vec3(0.0f, 25.0f, 0.0f) * Time::delta_time;
        }
    }
};

class lightMover : public Module
{
public:
    void Update()
    {
        if (Input::keys[SDLK_LEFT])
        {
            attached_to->transform.position += glm::vec3(1.0f, 0.0f, 0.0f) * Time::delta_time;
        }
        if (Input::keys[SDLK_RIGHT])
        {
            attached_to->transform.position -= glm::vec3(1.0f, 0.0f, 0.0f) * Time::delta_time;
        }
        if (Input::keys[SDLK_UP])
        {
            attached_to->transform.position += glm::vec3(0.0f, 1.0f, 0.0f) * Time::delta_time;
        }
        if (Input::keys[SDLK_DOWN])
        {
            attached_to->transform.position -= glm::vec3(0.0f, 1.0f, 0.0f) * Time::delta_time;
        }
    }
};

int main(int argc, char* args[])
{
    Core engine("Core Engine");
    //Create a new environment
    Environment::CreateEnvironment("default");
    //Create Default Camera
    std::shared_ptr<Camera> myCamera = Environment::CreateCamera("My Camera 1");
    //Create Default Light
    std::shared_ptr<Light> myLight = Environment::CreateLight("My Light");
    myLight->type = Light::LIGHT_TYPE::POINT;
    //Create Object

    std::shared_ptr<Shader> myShader = std::shared_ptr<Shader>(new Shader("defaultVS.glsl", "defaultFS.glsl"));
    std::shared_ptr<Surface> mySurface = std::shared_ptr<Surface>(new Surface(myShader));
    mySurface->ApplyTexture(std::shared_ptr<Texture>(new Texture("default.png")));
    std::shared_ptr<Entity> myObj = Environment::CreateEntity("My Object");
    std::shared_ptr<Mesh> myMesh = myObj->AddModule<Mesh>();
    myMesh->LoadOBJFile("monkey3.obj");
    myMesh->ApplySurface(mySurface);

    myCamera->AddModule<cameraMovment>();
    myObj->AddModule<modelRotator>();
    myLight->AddModule<lightMover>();

    engine.Start();
    
    return 0;
}