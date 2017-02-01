#include "Engine/Core/Core.h"

class cameraMovment : public Module
{
public:
    void Update()
    {
        if (Input::keys[SDLK_a])
        {
            attached_to->transform.position += attached_to->transform.Right() * Time::delta_time * 10.0f;
        }
        if (Input::keys[SDLK_d])
        {
            attached_to->transform.position -= attached_to->transform.Right() * Time::delta_time * 10.0f;
        }
        if (Input::keys[SDLK_w])
        {
            attached_to->transform.position += attached_to->transform.Forward() * Time::delta_time * 10.0f;
        }
        if (Input::keys[SDLK_s])
        {
            attached_to->transform.position -= attached_to->transform.Forward() * Time::delta_time * 10.0f;
        }
        if (Input::keys[SDLK_e])
        {
            attached_to->transform.Rotate(glm::vec3(0.0f, 10.0f, 0.0f) * Time::delta_time);
        }
        if (Input::keys[SDLK_q])
        {
            attached_to->transform.Rotate(glm::vec3(0.0f, -10.0f, 1.0f) * Time::delta_time);
        }
        if (Input::keys[SDLK_l])
        {
            attached_to->transform.position += attached_to->transform.Up() * Time::delta_time;
        }
        if (Input::keys[SDLK_k])
        {
            attached_to->transform.position -= attached_to->transform.Up() * Time::delta_time;
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
    myCamera->transform.position = glm::vec3(0.0f, 3.0f, 10.0f);
    myCamera->transform.Rotate(glm::vec3(0.0f, 180.0f, 0.0f));
    myCamera->AddModule<cameraMovment>();

    //Create Default Light
    std::shared_ptr<Light> myLight = Environment::CreateLight("My Light");
    myLight->type = Light::LIGHT_TYPE::DIRECTIONAL;
    myLight->transform.Rotate(glm::vec3(-90.0f, 0.0f, 0.0f));
    //Light Monkey Mesh
    std::shared_ptr<Shader> myShader = std::shared_ptr<Shader>(new Shader("GUI_3DVS.glsl", "GUI_3DFS.glsl"));
    std::shared_ptr<Surface> mySurface = std::shared_ptr<Surface>(new Surface(myShader));
    mySurface->ApplyTexture(std::shared_ptr<Texture>(new Texture("default.png")));
    std::shared_ptr<Mesh> myMesh = myLight->AddModule<Mesh>();
    myMesh->LoadOBJFile("monkey3.obj");
    myMesh->ApplySurface(mySurface);



    std::shared_ptr<Entity> myObj = Environment::CreateEntity("My Terrain");
    myObj->transform.Rotate(glm::vec3(0.0f, 180.0f, 0.0f));
    std::shared_ptr<Terrain> myTerrain = myObj->AddModule<Terrain>();
    myTerrain->CreateTerrain(100, 100, 1.0f);


    std::shared_ptr<Entity> myObj2 = Environment::CreateEntity("My Object");
    myObj2->transform.position = glm::vec3(0.0f, 0.0f, -50.0f);
    std::shared_ptr<Mesh> myMesh2 = myObj2->AddModule<Mesh>();
    myMesh2->LoadOBJFile("monkey3.obj");

    engine.Start();
    
    return 0;
}