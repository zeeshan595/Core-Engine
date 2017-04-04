#include "Engine/Common.h"
#include "Game/GameResources.h"
#include "Game/StartGame.h"
#include "Game/CameraMovment.h"
#include "Game/Player_Movement.h"
#include "Game/Obstacle.h"
#include "Game/Minimap.h"

int main(int argc, char* args[])
{

/*==========SCENE MANAGEMENT===========*/
    //Setup Window
    Screen::SetWindowTitle("Second Sight");
    Screen::SetResolution(1280, 720, false);
    Screen::SetScreenPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    //Create Scenes
    Environment* main_menu_scene = Environment::CreateEnvironment("Main Menu");
    Environment* game_scene = Environment::CreateEnvironment("Game");

    //Setup Main Menu
    Environment::SetEnvironment(main_menu_scene, false);    

    //Main Menu Camera
    Camera* menu_camera  = Environment::CreateCamera("Menu Camera");
    AudioSource* menu_audio_source = menu_camera->CreateModule<AudioSource>();
    AudioClip* menu_music_clip  = new AudioClip("isolation.wav");
    menu_audio_source->SetClip(menu_music_clip);    
    menu_audio_source->SetLooping(true);
    menu_camera->CreateModule<StartGame>();

/*==========MAIN MENU (UI)===========*/
    Shader* manu_background_ui_shader = new Shader("Default/uiVS.glsl", "Default/uiFS.glsl");
    Texture* manu_background_ui_texture = new Texture("menu.jpg");
    Entity* background_object = Environment::CreateEntity("UI Object");
    background_object->transform.SetPosition(glm::vec3(-1, -1, 0));
    background_object->transform.SetSize(glm::vec3(1, 1, 1));
    UI* background_ui_module = background_object->CreateModule<UI>();
    background_ui_module->SetShader(manu_background_ui_shader);
    background_ui_module->SetTexture(manu_background_ui_texture);

/*==========ENVIRONMENT OBJECTS===========*/

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
    AudioSource* game_audio_source = game_camera->CreateModule<AudioSource>();
    AudioClip* game_music_clip = new AudioClip("play.wav");
    game_audio_source->SetClip(game_music_clip);
    game_audio_source->SetLooping(true);
    game_camera->CreateModule<CameraMovment>();
    game_camera->SetNearClip(1.0f);

    Camera* minimap_camera = Environment::CreateCamera("Minimap Camera");
    minimap_camera->CreateModule<Minimap>();
    minimap_camera->transform.Rotate(glm::vec3(1.57f, 0, 0));
    minimap_camera->SetViewport(0.0f, 0.0f, 0.1f, 0.1f);
    minimap_camera->SetNearClip(1.0f);

    //Setup Terrain
    Entity* terrain_object = Environment::CreateEntity("Terrain");
    Terrain* terrain_module = terrain_object->CreateModule<Terrain>();
    terrain_object->CreateModule<MeshData>();
    MeshRenderer* terrain_renderer = terrain_object->CreateModule<MeshRenderer>();
    terrain_object->CreateModule<Rigidbody>(); // Terrain Module Auto sets collision shape
    terrain_renderer->SetMaterial(GameResources::terrain_material);

/*==========SCENE GAMEOBJECTS===========*/

    //Player
    Entity* player_object = Environment::CreateEntity("Player");    //Player Entity (GameObject)
    MeshData* player_object_mesh_module = player_object->CreateModule<MeshData>();  //Mesh Data (VBO/EBO/VAO)
    MeshRenderer* player_object_renderer_module = player_object->CreateModule<MeshRenderer>();  //Mesh MeshRenderer
    Rigidbody* player_object_rigidbody_module = player_object->CreateModule<Rigidbody>();   //RigidBody (Physics Calcs)
    player_object->CreateModule<PlayerMovement>();  //Input
    AudioSource* player_audio_module = player_object->CreateModule<AudioSource>();  //Audio Source
    AudioClip* player_sound  = new AudioClip("walk.wav"); //Sound effect
    player_audio_module->SetClip(player_sound); //Sound play properties
    player_audio_module->SetLooping(true);  //Sound play properties

    BoxCollider* player_collider_module = new BoxCollider(1.0f, 1.0f, 1.0f);  //Box Collider
    player_collider_module->SetColliderOffset(glm::vec3(0.0f, 0.5f, 0.0f));
    player_object_rigidbody_module->SetCollisionShape(player_collider_module);  //RigidBody
    player_object_mesh_module->LoadOBJ("cube.obj"); //Model
    player_object_renderer_module->SetMaterial(GameResources::player_material); //Texture Material
    player_object->transform.SetPosition(glm::vec3(50, 8, 50)); //Start Position
    player_object->transform.Rotate(glm::vec3(0, 0.0f, 0));   //Initial Rotation

    //Simple House
    Entity* house_object  = Environment::CreateEntity("House");
    MeshData* house_mesh_module = house_object->CreateModule<MeshData>();
    MeshRenderer* house_renderer_module = house_object->CreateModule<MeshRenderer>();
    // Rigidbody* house_object_rigidbody_module = house_object->CreateModule<Rigidbody>();   //RigidBody (Physics Calcs)
    // house_object->CreateModule<Obstacle>();  //Enable Collision
    // glm::vec3 house_size = house_object->transform.GetSize();
    // BoxCollider* house_collider_module = new BoxCollider(1.0f,1.0f,1.0f);  //Box Collider
    // // house_collider_module->SetColliderOffset(house_size);
    // house_collider_module->SetColliderOffset(glm::vec3(0.0f, 0.5f, 0.0f));
    
    // house_object_rigidbody_module->SetCollisionShape(house_collider_module);  //RigidBody

    house_mesh_module->LoadOBJ("Bambo_House.obj");
    house_renderer_module->SetMaterial(GameResources::building_material);
    house_object->transform.SetPosition(glm::vec3(50,7, 60)); //Start Position
    house_object->transform.SetSize(glm::vec3(0.5f, 0.5f, 0.5f)); //Initial Scale


    //Radio
    Entity* radio_object  = Environment::CreateEntity("radio");
    MeshData* radio_mesh_module = radio_object->CreateModule<MeshData>();
    MeshRenderer* radio_renderer_module = radio_object->CreateModule<MeshRenderer>();
    Rigidbody* radio_object_rigidbody_module = radio_object->CreateModule<Rigidbody>();   //RigidBody (Physics Calcs)
    glm::vec3 radio_size = radio_object->transform.GetSize();
    radio_object->CreateModule<Obstacle>();

    BoxCollider* radio_collider_module = new BoxCollider(radio_size.x, radio_size.y, radio_size.z);  //Box Collider
    radio_collider_module->SetColliderOffset(glm::vec3(0.0f, 0.5f, 0.0f));
    radio_object_rigidbody_module->SetCollisionShape(radio_collider_module);  //RigidBody
    
    radio_mesh_module->LoadOBJ("radio.obj");
    radio_renderer_module->SetMaterial(GameResources::radio_material);
    radio_object->transform.SetPosition(glm::vec3(50,10, 52)); //Start Position

    radio_object->transform.SetSize(glm::vec3(0.2f, 0.2f, 0.2f)); //Initial Scale
    radio_object->transform.Rotate(glm::vec3(0, 90.0f, 0));   //Initial Rotation


    //Square Crate
    Entity* crate_object  = Environment::CreateEntity("Crate 1");
    MeshData* crate_mesh_module = crate_object->CreateModule<MeshData>();
    MeshRenderer* crate_renderer_module = crate_object->CreateModule<MeshRenderer>();
    Rigidbody* crate_object_rigidbody_module = crate_object->CreateModule<Rigidbody>();
    glm::vec3 crate_size = crate_object->transform.GetSize();   //RigidBody (Physics Calcs)
    crate_object->CreateModule<Obstacle>();

    BoxCollider* crate_collider_module = new BoxCollider(crate_size.x, crate_size.y, crate_size.z);  //Box Collider
    crate_collider_module->SetColliderOffset(glm::vec3(0.0f, 0.5f, 0.0f));
    crate_object_rigidbody_module->SetCollisionShape(crate_collider_module);  //RigidBody

    crate_mesh_module->LoadOBJ("Crate1.obj");
    crate_renderer_module->SetMaterial(GameResources::crate_material);
    crate_object->transform.SetPosition(glm::vec3(40,7, 52)); //Start Position
    crate_object->transform.SetSize(glm::vec3(1.0f, 1.0f, 1.0f)); //Initial Scale
    crate_object->transform.Rotate(glm::vec3(0, 90.0f, 0));   //Initial Rotation


    //Long Crate
    Entity* crate_object2  = Environment::CreateEntity("Crate 2");
    MeshData* crate_mesh_module2 = crate_object2->CreateModule<MeshData>();
    MeshRenderer* crate_renderer_module2 = crate_object2->CreateModule<MeshRenderer>();
    Rigidbody* crate2_object_rigidbody_module = crate_object2->CreateModule<Rigidbody>();   //RigidBody (Physics Calcs)
    glm::vec3 crate_size2 = crate_object2->transform.GetSize();   //RigidBody (Physics Calcs)
    crate_object2->CreateModule<Obstacle>();

    BoxCollider* crate_collider_module2 = new BoxCollider(crate_size2.x, crate_size2.y, crate_size2.z);  //Box Collider
    crate_collider_module2->SetColliderOffset(glm::vec3(0.0f, 0.5f, 0.0f));
    crate2_object_rigidbody_module->SetCollisionShape(crate_collider_module2);  //RigidBody

    crate_mesh_module2->LoadOBJ("Crate2.obj");
    crate_renderer_module2->SetMaterial(GameResources::crate_material2);
    crate_object2->transform.SetPosition(glm::vec3(40,7, 50)); //Start Position
    crate_object2->transform.SetSize(glm::vec3(1.0f, 1.0f, 1.0f)); //Initial Scale
    crate_object2->transform.Rotate(glm::vec3(0, 90.0f, 0));   //Initial Rotation

    

/*==========GAME OVER (UI)===========*/

    engine.Start();
    //CleanUp
    GameResources::DestroyResources();
    //Destroy UI
    delete manu_background_ui_texture;
    delete manu_background_ui_shader;

    //Destroy Music
    delete menu_music_clip;
    delete game_music_clip;
    return 0;
}