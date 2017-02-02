#include "Engine/Core/Core.h"

class CameraMovment : public Module
{
public:
    std::shared_ptr<Entity> myPlayer;

    void Start(){
        myPlayer = Environment::FindEntity("Player");
    }

    void Update(){
        glm::vec3 offset = (-myPlayer->transform.Forward() * 5.0f) + (myPlayer->transform.Up() * 3.0f);
        attached_to->transform.position = myPlayer->transform.position + offset;
        attached_to->transform.rotation = glm::vec3(-25.0f, myPlayer->transform.rotation.y, 0.0f);
    }
};

class PlayerMovment : public Module
{
public:
    float speed = 10.0f;
    float rotation_speed = 1.0f;
    float gravity = 9.8f;
    std::shared_ptr<Terrain> myTerrain;

    void Start(){
        myTerrain = Environment::FindEntity("My Terrain")->GetModule<Terrain>();
    }

    void Update(){
        if (Input::keys[SDLK_a]){
            attached_to->transform.rotation += glm::vec3(0.0f, 1.0f, 0.0f) * rotation_speed * Time::delta_time;
        }
        if (Input::keys[SDLK_d]){
            attached_to->transform.rotation -= glm::vec3(0.0f, 1.0f, 0.0f) * rotation_speed * Time::delta_time;
        }
        if (Input::keys[SDLK_w]){
            attached_to->transform.position += attached_to->transform.Forward() * speed * Time::delta_time;
        }
        if (Input::keys[SDLK_s]){
            attached_to->transform.position -= attached_to->transform.Forward() * speed * Time::delta_time;
        }
        //Gravity
        attached_to->transform.position.y -= gravity * Time::delta_time;
        float min_y_pos = myTerrain->TerrainHeight(attached_to->transform.position.x, attached_to->transform.position.z);
        if (attached_to->transform.position.y < min_y_pos){
            attached_to->transform.position.y = min_y_pos;
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
    myCamera->AddModule<CameraMovment>();

    //Create Default Light
    std::shared_ptr<Light> myLight = Environment::CreateLight("My Light");
    myLight->type = Light::LIGHT_TYPE::DIRECTIONAL;
    myLight->transform.rotation = (glm::vec3(-90.0f, 0.0f, 25.0f));
    //Light Monkey Mesh
    std::shared_ptr<Shader> myShader = std::shared_ptr<Shader>(new Shader("ui_3dVS.glsl", "ui_3dFS.glsl"));
    std::shared_ptr<Surface> mySurface = std::shared_ptr<Surface>(new Surface(myShader));
    mySurface->ApplyTexture(std::shared_ptr<Texture>(new Texture("default.png")));
    std::shared_ptr<Mesh> myMesh = myLight->AddModule<Mesh>();
    myMesh->LoadOBJFile("monkey3.obj");
    myMesh->ApplySurface(mySurface);

    std::shared_ptr<Entity> myObj = Environment::CreateEntity("My Terrain");
    std::shared_ptr<Terrain> myTerrain = myObj->AddModule<Terrain>();
    myTerrain->CreateTerrain();

    std::shared_ptr<Entity> myObj2 = Environment::CreateEntity("Player");
    myObj2->transform.position = glm::vec3(20.0f, 5.0f, 20.0f);
    std::shared_ptr<Mesh> myMesh2 = myObj2->AddModule<Mesh>();
    myMesh2->LoadOBJFile("monkey3.obj");
    myObj2->AddModule<PlayerMovment>();

    std::shared_ptr<Entity> UIobj = Environment::CreateEntity("My GUI");
    std::shared_ptr<UIMesh> myUI = UIobj->AddModule<UIMesh>();
    myUI->rect = glm::vec4(-Screen::width, Screen::height - 100.0f, 100.0f, 100.0f);
    myUI->rotation = 0.0f;

    engine.Start();
    return 0;
}