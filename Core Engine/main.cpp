#include "Engine/Core/Core.h"

class MyCustomModule : public NonRenderingModule
{
    void Update()
    {
        if (keys_pressed[SDLK_d])
        {
            attached_camera->transform.rotation -= glm::vec3(0, 50, 0) * delta_time;
        }
        if (keys_pressed[SDLK_a])
        {
            attached_camera->transform.rotation += glm::vec3(0, 50, 0) * delta_time;
        }
        if (keys_pressed[SDLK_w])
        {
            attached_camera->transform.position += attached_camera->transform.Forward() * delta_time * 5.0f;
        }
        if (keys_pressed[SDLK_s])
        {
            attached_camera->transform.position -= attached_camera->transform.Forward() * delta_time * 5.0f;
        }
    }
};

class MyCustomModule2 : public NonRenderingModule
{
    void Update()
    {
        if (keys_pressed[SDLK_UP])
        {
            attached_light->transform.position += glm::vec3(0, 1, 0) * delta_time * 5.0f;
        }
        if (keys_pressed[SDLK_DOWN])
        {
            attached_light->transform.position -= glm::vec3(0, 1, 0) * delta_time * 5.0f;
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

    //Add mycustom Module
    camera_1->AddModule<MyCustomModule>();

    //Create Light
    std::shared_ptr<Light> light1 = engine->world->CreateLight(Light::LIGHT_TYPE::POINT);
    light1->transform.position = glm::vec3(0, 20, 0);
    light1->light_range = 10.0f;
    light1->brightness = 1.0f;
    light1->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    //Add mycustom Module
    light1->AddModule<MyCustomModule2>();

    //Create a new Cube object
    std::shared_ptr<Entity> myObj = engine->world->CreateEntity("Cube");
    //Attach Mesh Component So It Is Renders (If no shader is specified it creates a default one)
    std::shared_ptr<Mesh> myMesh = myObj->AddModule<Mesh>();
    //Load obj mesh
    myMesh->LoadModel("monkey3.obj");  // OR myMesh->LoadDefaultCube();
    //Create new Surface (this includes shader and texture)
    std::shared_ptr<Surface> mySurface = std::shared_ptr<Surface>(new Surface("defaultVS.glsl", "defaultFS.glsl"));
    mySurface->ApplyTexture("default.png");
    //Apply Texture and shader to the mesh
    myMesh->ApplySurface(mySurface);

    //Create a new Cube object
    std::shared_ptr<Entity> myObj2 = engine->world->CreateEntity("Cube");
    myObj2->transform.position = glm::vec3(0, -2.0f, 0.0f);
    //Attach Mesh Component So It Is Renders (If no shader is specified it creates a default one)
    std::shared_ptr<Mesh> myMesh2 = myObj2->AddModule<Mesh>();
    //Load obj mesh
    myMesh2->LoadDefaultCube();
    //Apply Texture and shader to the mesh
    myMesh2->ApplySurface(mySurface);

    engine->Start();
    return 0;
}