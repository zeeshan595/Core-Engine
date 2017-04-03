#include "Engine/Common.h"
#include "Game/GameResources.h"
#include "Game/MenuManager.h"
#include "Game/CameraMovment.h"
#include "Game/CarMovment.h"

int main(int argc, char* args[])
{
    //Setup Window
    Screen::SetWindowTitle("The Car Game");
    Screen::SetResolution(1920, 1080, false);
    Screen::SetScreenPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    //Create Scenes
    Environment* main_menu_scene    = Environment::CreateEnvironment("Main Menu");
    Environment* game_scene         = Environment::CreateEnvironment("test");

    //Setup Main Menu
    Environment::SetEnvironment(main_menu_scene, false);

    //Main Menu Camera
    Camera* menu_camera = Environment::CreateCamera("Menu Camera");
    menu_camera->CreateModule<MenuManager>();

    //Main Menu Background UI
    Shader* manu_background_ui_shader = new Shader("Default/uiVS.glsl", "Default/uiFS.glsl");
    Texture* manu_background_ui_texture = new Texture("texture.png");
    Entity* background_object = Environment::CreateEntity("UI Object");
    background_object->transform.SetPosition(glm::vec3(0, 0, 0));
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
    Camera* game_camera = Environment::CreateCamera("Game Camera");
    game_camera->CreateModule<CameraMovment>();
    game_camera->SetNearClip(1.0f);

    //Setup Terrain
    Entity* terrain_object              = Environment::CreateEntity("Terrain");
    Terrain* terrain_module             = terrain_object->CreateModule<Terrain>();
                                          terrain_object->CreateModule<MeshData>();
    MeshRenderer* terrain_renderer      = terrain_object->CreateModule<MeshRenderer>();
                                          terrain_object->CreateModule<Rigidbody>(); // Terrain Module Auto sets collision shape
    terrain_renderer->SetMaterial(GameResources::terrain_material);
    game_camera->CreateModule<CameraMovment>();

    //Create Car
    Entity* car_object                  = Environment::CreateEntity("Car");
    MeshData* car_mesh_module           = car_object->CreateModule<MeshData>();
    MeshRenderer* car_renderer_module   = car_object->CreateModule<MeshRenderer>();
    Rigidbody* car_rigidbody_module     = car_object->CreateModule<Rigidbody>();
                                          car_object->CreateModule<CarMovment>();
    BallCollider* car_collider_module   = new BallCollider(0.5f);
    car_collider_module->SetColliderOffset(glm::vec3(0.0f, 0.5f, 0.0f));
    car_rigidbody_module->SetCollisionShape(car_collider_module);
    car_mesh_module->LoadOBJ("car.obj");
    car_renderer_module->SetMaterial(GameResources::car_material);
    car_object->transform.SetPosition(glm::vec3(5, 3, 5));

    engine.Start();
    //CleanUp
    GameResources::DestroyResources();
    delete manu_background_ui_texture;
    delete manu_background_ui_shader;
    return 0;
}