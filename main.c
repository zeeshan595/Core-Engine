#include "Engine/Core/Core.h"
#include "Game/CameraMovment.h"



int main(int argc, char* args[])
{
    Core engine("Core Engine");
    Screen::SetResolution(1920, 1080, false);
    glm::vec2 screen_size = Screen::GetDisplayResolution();
    Screen::SetScreenPosition( (screen_size.x / 2) - (Screen::width / 2), (screen_size.y / 2) - (Screen::height / 2) );
    //Environment::GetSkybox(); //use this to edit skybox
    //Create a new environment
    Environment::CreateEnvironment("default");
    Quality::texture_filter = TextureFilterType::ANISOTROPIC;
    Quality::anistropic_filter_amount = Quality::GetMaxAnistropicAmount();
    Quality::EnableMultisampling(); //Add Multisample-Antialiasing

    std::shared_ptr<Camera> myCamera2 = Environment::CreateCamera("My Camera 2");
    myCamera2->transform.position = glm::vec3(50, 5, 50);
    myCamera2->transform.rotation = glm::vec3(0, 0, 0);
    myCamera2->draw_order = 1;
    myCamera2->viewport = glm::vec4(0, 0, 0.3f, 0.3f);

    //Create Default Camera
    std::shared_ptr<Camera> myCamera = Environment::CreateCamera("My Camera 1");
    myCamera->draw_order = 0;
    myCamera->AddModule<CameraMovment>();

    //Create Default Light
    std::shared_ptr<Light> myLight = Environment::CreateLight("My Light");
    myLight->type = Light::LIGHT_TYPE::DIRECTIONAL;
    myLight->transform.rotation = (glm::vec3(-90.0f, 0.0f, 25.0f));

    //Generate Teerain
    std::shared_ptr<Entity> myObj = Environment::CreateEntity("My Terrain");
    std::shared_ptr<Terrain> myTerrain = myObj->AddModule<Terrain>();
    //Change all terrain variables here
    myTerrain->CreateTerrain();

    //Create GUI
    UI::CreateUI(std::shared_ptr<Texture>(new Texture("texture.png")), glm::vec4(0.0f, 0, 100.0f, 100.0f));

    //Create 2D Audio. For 3D attach AudioClip to a Entity
    std::shared_ptr<AudioSource> myAudio = myLight->AddModule<AudioSource>();
    std::shared_ptr<AudioClip> myClip = std::shared_ptr<AudioClip>(new AudioClip("song.wav"));
    myAudio->SetClip(myClip);
    myAudio->play_on_start = true;
    //myAudio->SetLooping(true);

    //Create Particle System
    std::shared_ptr<ParticleSystem> ps = myLight->AddModule<ParticleSystem>();
    std::shared_ptr<Surface> surface4 = std::shared_ptr<Surface>(new Surface(std::shared_ptr<Shader>(new Shader("default/particleVS.glsl", "default/particleFS.glsl"))));
    surface4->AddTexture(std::shared_ptr<Texture>(new Texture("texture.png")));
    ps->ApplySurface(surface4);
    myLight->transform.position = glm::vec3(0, 3, 0);

    //Normal Map Texture
    std::shared_ptr<Entity> normal_test_entity = Environment::CreateEntity("Normal Map Test Object");
    std::shared_ptr<Mesh> normal_test_mesh = normal_test_entity->AddModule<Mesh>();
    normal_test_mesh->LoadDefaultPlane();
    std::shared_ptr<Surface> surface5 = std::shared_ptr<Surface>(new Surface(std::shared_ptr<Shader>(new Shader("default/defaultVS.glsl", "default/defaultFS.glsl"))));
    surface5->AddTexture(std::shared_ptr<Texture>(new Texture("boulder.png")));
    surface5->AddTexture(std::shared_ptr<Texture>(new Texture("boulder_normal.png")));
    normal_test_mesh->ApplySurface(surface5);
    normal_test_entity->transform.rotation = glm::vec3(-90, 0, 0);
    normal_test_entity->transform.position = glm::vec3(10, 10, 10);

    //Physics Test
    std::shared_ptr<Entity> bt_box = Environment::CreateEntity("Physics Cube");
    std::shared_ptr<Mesh> bt_box_mesh = bt_box->AddModule<Mesh>();
    bt_box_mesh->ApplySurface(surface5);
    bt_box_mesh->LoadDefaultCube();
    bt_box->transform.position = glm::vec3(50, 10, 50);
    bt_box->transform.scale = glm::vec3(20, 1, 20);
    std::shared_ptr<BoxCollider> box_coll = bt_box->AddModule<BoxCollider>();
    box_coll->mass = 0.0f;//so the ground doesn't move

    std::shared_ptr<Entity> bt_box2 = Environment::CreateEntity("Physics Cube");
    std::shared_ptr<Mesh> bt_box_mesh2 = bt_box2->AddModule<Mesh>();
    std::shared_ptr<Surface> surface6 = std::shared_ptr<Surface>(new Surface(std::shared_ptr<Shader>(new Shader("default/defaultVS.glsl", "default/defaultFS.glsl"))));
    surface6->AddTexture(std::shared_ptr<Texture>(new Texture("mud.png")));
    surface6->AddTexture(std::shared_ptr<Texture>(new Texture("boulder_normal.png")));
    bt_box_mesh2->ApplySurface(surface6);
    bt_box_mesh2->LoadDefaultCube();
    bt_box2->transform.position = glm::vec3(50, 13, 50);
    bt_box2->transform.scale = glm::vec3(1, 1, 1);
    bt_box2->AddModule<BoxCollider>();


    engine.EnableDebugMode();
    engine.Start();
    return 0;
}