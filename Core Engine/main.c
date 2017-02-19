#include "Engine/Core/Core.h"
#include "Game/CameraMovment.h"

int main(int argc, char* args[])
{
    Screen::width = 1920;
    Screen::height = 1080;
    Core engine("Core Engine");
    //Environment::GetSkybox(); //use this to edit skybox
    //Create a new environment
    Environment::CreateEnvironment("default");
    Quality::texture_filter = TextureFilterType::ANISOTROPIC;
    Quality::anistropic_filter_amount = Quality::GetMaxAnistropicAmount();
    Quality::EnableMultisampling(); //Add Multisample-Antialiasing

    std::shared_ptr<Camera> myCamera2 = Environment::CreateCamera("My Camera 2");
    myCamera2->transform.position = glm::vec3(50, 20, 50);
    myCamera2->transform.rotation = glm::vec3(90, 0, 180);
    myCamera2->draw_order = 1;
    myCamera2->viewport = glm::vec4(0, 0, 0.3f, 0.3f);
    std::shared_ptr<Gizmo> gizmo = myCamera2->AddModule<Gizmo>();
    gizmo->ApplyTexture(std::shared_ptr<Texture>(new Texture("camera.png")));

    //Create Default Camera
    std::shared_ptr<Camera> myCamera = Environment::CreateCamera("My Camera 1");
    myCamera->draw_order = 0;
    myCamera->AddModule<CameraMovment>();
    std::shared_ptr<Gizmo> gizmo2 = myCamera->AddModule<Gizmo>();
    gizmo2->ApplyTexture(std::shared_ptr<Texture>(new Texture("camera.png")));

    //Create Default Light
    std::shared_ptr<Light> myLight = Environment::CreateLight("My Light");
    myLight->type = Light::LIGHT_TYPE::DIRECTIONAL;
    myLight->transform.rotation = (glm::vec3(-90.0f, 0.0f, 25.0f));
    std::shared_ptr<Gizmo> gizmo3 = myLight->AddModule<Gizmo>();
    gizmo3->ApplyTexture(std::shared_ptr<Texture>(new Texture("light.png")));

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

    engine.Start();
    return 0;
}