#include "Engine/Core/Core.h"

std::shared_ptr<Particle> p;

class CameraMovment : public Module
{
public:
    std::shared_ptr<Entity> myPlayer;
    float rotation_speed = 3.0f;
    float camera_rotation = 0.0f;

    void Start(){
        myPlayer = Environment::FindEntity("Player");
    }

    void Update(){
        glm::vec3 offset =  myPlayer->transform.Up() * 0.5f;
        attached_to->transform.position = myPlayer->transform.position + offset;

        camera_rotation += Input::mouse_delta.y * Time::delta_time * rotation_speed;
        camera_rotation = Transform::ToRadians(glm::clamp(Transform::ToDegrees(camera_rotation), -60.0f, 60.0f));
        attached_to->transform.rotation = glm::vec3(camera_rotation, myPlayer->transform.rotation.y, 0.0f);

        //Set listner to camera position
        Audio::ChangeListenerPosition(attached_to->transform.position);
        Audio::ChangeListenerOrientation(attached_to->transform.Forward(), attached_to->transform.Up());
    }
};

class PlayerMovment : public Module
{
public:
    float speed = 10.0f;
    float rotation_speed = 3.0f;
    float gravity = 9.8f;
    int tester = 0;
    std::shared_ptr<Terrain> myTerrain;

    void Start(){
        myTerrain = Environment::FindEntity("My Terrain")->GetModule<Terrain>();
        Input::LockCursor(true);
    }

    void Update(){
        if (Input::keys[SDLK_a]){
            attached_to->transform.position += attached_to->transform.Right() * speed * Time::delta_time;
        }
        if (Input::keys[SDLK_d]){
            attached_to->transform.position -= attached_to->transform.Right() * speed * Time::delta_time;
        }
        if (Input::keys[SDLK_w]){
            attached_to->transform.position += attached_to->transform.Forward() * speed * Time::delta_time;
        }
        if (Input::keys[SDLK_s]){
            attached_to->transform.position -= attached_to->transform.Forward() * speed * Time::delta_time;
        }
        if (Input::keys_down[SDLK_ESCAPE]){
            Input::LockCursor(false);
        }
        if (Input::mouse_down[SDL_BUTTON_LEFT]){
            Input::LockCursor(true);
        }
        //Rotation
        attached_to->transform.rotation -= glm::vec3(0.0f, 1.0f, 0.0f) * rotation_speed * Time::delta_time * Input::mouse_delta.x;

        //Gravity
        attached_to->transform.position.y -= gravity * Time::delta_time;
        float min_y_pos = myTerrain->TerrainHeight(attached_to->transform.position.x, attached_to->transform.position.z);
        if (attached_to->transform.position.y < min_y_pos){
            attached_to->transform.position.y = min_y_pos;
        }

        glm::vec3 ray = Raycast::GetRay(glm::vec2(Screen::width / 2, Screen::height / 2));
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

    std::shared_ptr<Camera> myCamera2 = Environment::CreateCamera("My Camera 2");
    myCamera2->draw_order = 1;
    myCamera2->viewport = glm::vec4(0, 0, 0.3f, 0.3f);

    //Create Default Light
    std::shared_ptr<Light> myLight = Environment::CreateLight("My Light");
    myLight->type = Light::LIGHT_TYPE::DIRECTIONAL;
    myLight->transform.rotation = (glm::vec3(-90.0f, 0.0f, 25.0f));
    //Light Monkey Mesh
    /*
    std::shared_ptr<Shader> myShader = std::shared_ptr<Shader>(new Shader("default/ui_3dVS.glsl", "default/ui_3dFS.glsl"));
    std::shared_ptr<Surface> mySurface = std::shared_ptr<Surface>(new Surface(myShader));
    mySurface->ApplyTexture(std::shared_ptr<Texture>(new Texture("default.png")));
    std::shared_ptr<Mesh> myMesh = myLight->AddModule<Mesh>();
    myMesh->LoadOBJFile("monkey3.obj");
    myMesh->ApplySurface(mySurface);
    */

    //Generate Teerain
    std::shared_ptr<Entity> myObj = Environment::CreateEntity("My Terrain");
    std::shared_ptr<Terrain> myTerrain = myObj->AddModule<Terrain>();
    //Change all terrain variables here
    myTerrain->CreateTerrain();

    //Create Player
    std::shared_ptr<Entity> myObj2 = Environment::CreateEntity("Player");
    //myObj2->transform.position = glm::vec3(20.0f, 5.0f, 20.0f);
    myObj2->AddModule<PlayerMovment>();

    //Create GUI
    UI::CreateUI("texture.png", glm::vec4(0.0f, 0, 100.0f, 100.0f));

    //Create 2D Audio. For 3D attach AudioClip to a Entity
    std::shared_ptr<AudioSource> myAudio = myLight->AddModule<AudioSource>();
    std::shared_ptr<AudioClip> myClip = std::shared_ptr<AudioClip>(new AudioClip("song.wav"));
    myAudio->SetClip(myClip);
    myAudio->play_on_start = false;
    //myAudio->SetLooping(true);

    //Create Particle System
    myLight->AddModule<ParticleSystem>();
    myLight->transform.position = glm::vec3(0, 2, 0);

    //Environment::GetSkybox(); //use this to edit skybox

    engine.Start();
    return 0;
}