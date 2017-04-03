#include "Engine/Common.h"
#include "Game/GameResources.h"
#include "Game/MenuManager.h"
#include "Game/EndSceneManager.h"
#include "Game/CameraMovment.h"
#include "Game/CarMovment.h"
#include "Game/Minimap.h"

int main(int argc, char* args[])
{
    //Setup Window
    Screen::SetWindowTitle("The Car Game");
    Screen::SetResolution(1280, 720, false);
    Screen::SetScreenPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    //Create Scenes
    Environment* main_menu_scene    = Environment::CreateEnvironment("Main Menu");
    Environment* game_scene         = Environment::CreateEnvironment("Game");
    Environment* end_scene          = Environment::CreateEnvironment("End Scene");

    //Setup Main Menu
    Environment::SetEnvironment(main_menu_scene, false);

    //Main Menu Camera
    Camera* menu_camera             = Environment::CreateCamera("Menu Camera");
    AudioSource* menu_audio_source  = menu_camera->CreateModule<AudioSource>();
    AudioClip* menu_music_clip      = new AudioClip("menu.wav");
    menu_audio_source->SetClip(menu_music_clip);
    menu_audio_source->SetLooping(true);
    menu_camera->CreateModule<MenuManager>();

    //Main Menu Background UI
    Shader* manu_background_ui_shader = new Shader("Default/uiVS.glsl", "Default/uiFS.glsl");
    Texture* manu_background_ui_texture = new Texture("menu_background.png");
    Entity* background_object = Environment::CreateEntity("UI Object");
    background_object->transform.SetPosition(glm::vec3(-1, -1, 0));
    background_object->transform.SetSize(glm::vec3(1, 1, 1));
    UI* background_ui_module = background_object->CreateModule<UI>();
    background_ui_module->SetShader(manu_background_ui_shader);
    background_ui_module->SetTexture(manu_background_ui_texture);

    //Setup Game Scene
    Environment::SetEnvironment(game_scene, false);
    GameResources::SetupResources();

    //Game Scene Skybox
    Environment::SetSkybox(GameResources::skybox);

    //Game Lighting
    Light* game_light = Environment::CreateLight("Light");
    game_light->SetLightType(Light::LIGHT_TYPE::DIRECTIONAL);
    game_light->transform.Rotate(glm::vec3(130.0f, 0.0f, 0.0f));

    //Game Scene Camera
    Camera* game_camera             = Environment::CreateCamera("Game Camera");
    AudioSource* game_audio_source  = game_camera->CreateModule<AudioSource>();
    AudioClip* game_music_clip      = new AudioClip("game.wav");
    game_audio_source->SetClip(game_music_clip);
    game_audio_source->SetLooping(true);
    game_camera->CreateModule<CameraMovment>();
    game_camera->SetNearClip(1.0f);

    Camera* minimap_camera          = Environment::CreateCamera("Minimap Camera");
    minimap_camera->CreateModule<Minimap>();
    minimap_camera->transform.Rotate(glm::vec3(1.57f, 0, 0));
    minimap_camera->SetViewport(0.0f, 0.0f, 0.1f, 0.1f);
    minimap_camera->SetNearClip(1.0f);

    //Setup Terrain
    Entity* terrain_object              = Environment::CreateEntity("Terrain");
    Terrain* terrain_module             = terrain_object->CreateModule<Terrain>();
                                          terrain_object->CreateModule<MeshData>();
    MeshRenderer* terrain_renderer      = terrain_object->CreateModule<MeshRenderer>();
                                          terrain_object->CreateModule<Rigidbody>(); // Terrain Module Auto sets collision shape
    terrain_renderer->SetMaterial(GameResources::terrain_material);

    //Create Car
    Entity* car_object                  = Environment::CreateEntity("Car");
    MeshData* car_mesh_module           = car_object->CreateModule<MeshData>();
    MeshRenderer* car_renderer_module   = car_object->CreateModule<MeshRenderer>();
    Rigidbody* car_rigidbody_module     = car_object->CreateModule<Rigidbody>();
                                          car_object->CreateModule<CarMovment>();
    AudioSource* car_audio_module       = car_object->CreateModule<AudioSource>();
    AudioClip* car_sound                = new AudioClip("car.wav");
    car_audio_module->SetClip(car_sound);
    car_audio_module->SetLooping(true);
    BallCollider* car_collider_module   = new BallCollider(0.5f);
    car_collider_module->SetColliderOffset(glm::vec3(0.0f, 0.5f, 0.0f));
    car_rigidbody_module->SetCollisionShape(car_collider_module);
    car_mesh_module->LoadOBJ("car.obj");
    car_renderer_module->SetMaterial(GameResources::car_material);
    car_object->transform.SetPosition(glm::vec3(84, 2, 10));
    car_object->transform.Rotate(glm::vec3(0, -1.57f, 0));


    //Setup Main Menu
    Environment::SetEnvironment(end_scene, false);

    //Main Menu Camera
    Camera* end_camera              = Environment::CreateCamera("Menu Camera");
    AudioSource* end_audio_source   = end_camera->CreateModule<AudioSource>();
    AudioClip* end_music_clip       = new AudioClip("end.wav");
    end_audio_source->SetClip(end_music_clip);
    end_audio_source->SetLooping(true);
    end_camera->CreateModule<EndSceneManager>();

    //Main Menu Background UI
    Shader* end_background_ui_shader = new Shader("Default/uiVS.glsl", "Default/uiFS.glsl");
    Texture* end_background_ui_texture = new Texture("end_background.png");
    Entity* end_background_object = Environment::CreateEntity("UI Object");
    end_background_object->transform.SetPosition(glm::vec3(-1, -1, 0));
    end_background_object->transform.SetSize(glm::vec3(1, 1, 1));
    UI* end_background_ui_module = end_background_object->CreateModule<UI>();
    end_background_ui_module->SetShader(end_background_ui_shader);
    end_background_ui_module->SetTexture(end_background_ui_texture);

    engine.Start();
    //CleanUp
    GameResources::DestroyResources();
    //Destroy UI
    delete manu_background_ui_texture;
    delete manu_background_ui_shader;
    delete end_background_ui_shader;
    delete end_background_ui_texture;

    //Destroy Music
    delete car_sound;
    delete menu_music_clip;
    delete game_music_clip;
    delete end_music_clip;
    return 0;
}