#include "Engine/Core/Core.h"
#include "Game/CameraMovment.h"

int main(int argc, char* args[])
{
    Core engine("Core Engine");
    Screen::ChangeResolution(1920, 1080, false);
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
    myAudio->play_on_start = false;
    //myAudio->SetLooping(true);

    //Create Particle System
    std::shared_ptr<ParticleSystem> ps = myLight->AddModule<ParticleSystem>();
    std::shared_ptr<Surface> surface4 = std::shared_ptr<Surface>(new Surface(std::shared_ptr<Shader>(new Shader("default/particleVS.glsl", "default/particleFS.glsl"))));
    surface4->ApplyTexture(std::shared_ptr<Texture>(new Texture("texture.png")));
    ps->ApplySurface(surface4);
    myLight->transform.position = glm::vec3(0, 3, 0);

    //Normal Map Texture
    std::shared_ptr<Entity> normal_test_entity = Environment::CreateEntity("Normal Map Test Object");
    std::shared_ptr<Mesh> normal_test_mesh = normal_test_entity->AddModule<Mesh>();
    normal_test_mesh->LoadDefaultPlane();
    std::shared_ptr<Surface> surface5 = std::shared_ptr<Surface>(new Surface(std::shared_ptr<Shader>(new Shader("default/defaultVS.glsl", "default/defaultFS.glsl"))));
    surface5->ApplyTexture(std::shared_ptr<Texture>(new Texture("boulder.png")));
    surface5->ApplyTexture(std::shared_ptr<Texture>(new Texture("boulder_normal.png")));
    normal_test_mesh->ApplySurface(surface5);
    normal_test_entity->transform.rotation = glm::vec3(-90, 0, 0);
    normal_test_entity->transform.position = glm::vec3(10, 10, 10);

    engine.EnableDebugMode();
    engine.DisableDebugMode();
    engine.Start();
    return 0;
}