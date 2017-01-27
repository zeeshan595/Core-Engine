#include "Engine/header/Common.h"
#include "Engine/header/Core.h"

class MyCustomModule : public Module
{
    void Render(std::shared_ptr<Camera> camera, std::vector<std::shared_ptr<Light>> lights)
    {
        if (keys_pressed[SDLK_d])
        {
            camera->transform.rotation -= glm::vec3(0, 50, 0) * delta_time;
        }
        if (keys_pressed[SDLK_a])
        {
            camera->transform.rotation += glm::vec3(0, 50, 0) * delta_time;
        }
        if (keys_pressed[SDLK_w])
        {
            camera->transform.position += camera->transform.Forward() * delta_time * 5.0f;
        }
        if (keys_pressed[SDLK_s])
        {
            camera->transform.position -= camera->transform.Forward() * delta_time * 5.0f;
        }
    }
};

int main(int argc, char* args[])
{
    std::shared_ptr<Core> engine = std::shared_ptr<Core>(new Core());

    engine->world = std::shared_ptr<World>(new World());

    //Create Camera
    std::shared_ptr<Camera> camera_1 = engine->world->CreateCamera();
    //Specify how much space the camera takes up in the window
    camera_1->viewport_x = 0;
    camera_1->viewport_y = 0;
    camera_1->viewport_size_x = 1; //Value between 0 and 1. (0.5 is middle of the screen)
    camera_1->viewport_size_y = 1;

    
    
    //Create Light
    std::shared_ptr<Light> light1 = engine->world->CreateLight(Light::LIGHT_TYPE::DIRECTIONAL);
    light1->transform.rotation = glm::vec3(-90, 0, 45);


    //Create a new Cube object
    std::shared_ptr<Entity> myObj = engine->world->CreateEntity("Cube");
    //Attach Mesh Component So It Is Renders (If no shader is specified it creates a default one)
    std::shared_ptr<Mesh> myMesh = myObj->AddModule<Mesh>();
    //Load obj mesh
    myMesh->LoadModel("monkey3.obj");  // OR myMesh->LoadDefaultCube();
    //Create new Surface (this includes shader and texture)
    std::shared_ptr<Surface> mySurface = std::shared_ptr<Surface>(new Surface("defaultVS.glsl", "defaultFS.glsl"));
    mySurface->ApplyTexture("texture.png");
    //Apply Texture and shader to the mesh
    myMesh->ApplySurface(mySurface);

    //Add mycustom Module
    myObj->AddModule<MyCustomModule>();

    engine->Start();
    return 0;
}