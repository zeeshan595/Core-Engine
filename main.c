#include "Engine/Common.h"
#include "Game/CameraMovment.h"

class TestModule : public Module
{
public:
    void Update()
    {
        if (Input::keys_down[SDLK_RIGHT])
        {
            Environment::ChangeEnvironment(0);
        }
        if (Input::keys_down[SDLK_LEFT])
        {
            Environment::ChangeEnvironment(1);
        }
    }
};

int main(int argc, char* args[])
{
    Core engine("Core Engine");
    Screen::SetResolution(1920, 1080, false);
    glm::vec2 screen_size = Screen::GetDisplayResolution();
    Screen::SetScreenPosition( (screen_size.x / 2) - (Screen::width / 2), (screen_size.y / 2) - (Screen::height / 2) );

    Quality::texture_filter = TextureFilterType::ANISOTROPIC;
    Quality::anistropic_filter_amount = Quality::GetMaxAnistropicAmount();
    Quality::EnableMultisampling(); //Add Multisample-Antialiasing

    //Environment::GetSkybox(); //use this to edit skybox

    //Create a new environment
    Environment::CreateEnvironment("default");
    Environment::CreateEnvironment("scene");
    std::cout << Environment::GetEnvironmentSize() << std::endl;
    
    std::shared_ptr<Camera> myCamera2 = Environment::CreateCamera("My Camera 2");
    myCamera2->transform.Translate(glm::vec3(50, 5, 50));
    myCamera2->transform.Rotate(glm::vec3(90.0f, 0.0f, 0.0f));
    myCamera2->draw_order = 1;
    myCamera2->viewport = glm::vec4(0, 0, 0.3f, 0.3f);
    myCamera2->AddModule<TestModule>();

    Environment::ChangeEnvironment("scene");

    //Create Default Camera
    std::shared_ptr<Camera> myCamera = Environment::CreateCamera("My Camera 1");
    myCamera->draw_order = 0;
    myCamera->AddModule<CameraMovment>();
    //myCamera->AddModule<TestModule>();

    //Create Default Light
    std::shared_ptr<Light> myLight = Environment::CreateLight("My Light");
    myLight->type = Light::LIGHT_TYPE::DIRECTIONAL;
    myLight->transform.Rotate(glm::vec3(-45.0f, 0.0f, 0.0));

    //Generate Terrain
    std::shared_ptr<Entity> myObj = Environment::CreateEntity("My Terrain");
    std::shared_ptr<Terrain> myTerrain = myObj->AddModule<Terrain>();
    //Change all terrain variables here
    myTerrain->CreateTerrain();
    std::shared_ptr<Rigidbody> terrain_coll = myObj->AddModule<Rigidbody>();
    terrain_coll->SetCollisionShape(std::shared_ptr<TerrainCollider>(new TerrainCollider(myTerrain->GetTerrainCollisionInfo())));
    terrain_coll->SetMass(0.0f);//Make terrain static

    //Create GUI
    UI::CreateUI(std::shared_ptr<Texture>(new Texture("texture.png")), glm::vec4(0.0f, 0, 100.0f, 100.0f));
    UI::CreateUI(std::shared_ptr<Texture>(new Texture("crate.png")), glm::vec4(100.0f, 100.0f, 100.0f, 100.0f));

    //Create Audio
    std::shared_ptr<AudioSource> myAudio = myLight->AddModule<AudioSource>();
    std::shared_ptr<AudioClip> myClip = std::shared_ptr<AudioClip>(new AudioClip("song.wav"));
    myAudio->SetClip(myClip);
    myAudio->play_on_start = false;
    //myAudio->SetLooping(true);

    //Create Particle System
    std::shared_ptr<ParticleSystem> ps = myLight->AddModule<ParticleSystem>();
    std::shared_ptr<Surface> surface4 = std::shared_ptr<Surface>(new Surface(std::shared_ptr<Shader>(new Shader("default/particleVS.glsl", "default/particleFS.glsl"))));
    surface4->SetColorMap(std::shared_ptr<Texture>(new Texture("texture.png")));
    ps->SetSurface(surface4);
    myLight->transform.Translate(glm::vec3(0, 3, 0));

    //Normal Map Texture
    std::shared_ptr<Entity> normal_test_entity = Environment::CreateEntity("Normal Map Test Object");
    std::shared_ptr<Mesh> normal_test_mesh = normal_test_entity->AddModule<Mesh>();
    normal_test_mesh->LoadDefaultPlane();
    std::shared_ptr<Surface> surface5 = Surface::LoadDefaultSurface();
    surface5->SetColorMap(std::shared_ptr<Texture>(new Texture("boulder.png")));
    surface5->SetNormalMap(std::shared_ptr<Texture>(new Texture("boulder_normal.png")));
    normal_test_mesh->SetSurface(surface5);
    //normal_test_entity->transform.rotation = glm::vec3(-130, 0, 0);
    normal_test_entity->transform.Translate(glm::vec3(10, 10, 10));

    //Physics Test
    std::shared_ptr<Entity> bt_box = Environment::CreateEntity("Physics Cube");
    std::shared_ptr<Mesh> bt_box_mesh = bt_box->AddModule<Mesh>();
    bt_box_mesh->SetSurface(Surface::LoadDefaultSurface());
    bt_box_mesh->LoadDefaultCube();
    bt_box->transform.Translate(glm::vec3(50, 13, 50));
    //bt_box->transform.rotation = glm::vec3(60, 0, 0);
    bt_box->transform.Scale(glm::vec3(1, 1, 1));
    //std::shared_ptr<BoxCollider> box_coll = bt_box->AddModule<BoxCollider>();
    //box_coll->mass = 0.0f;//so the ground doesn't move

    std::shared_ptr<Entity> bt_box2 = Environment::CreateEntity("Physics Cube");
    std::shared_ptr<Mesh> bt_box_mesh2 = bt_box2->AddModule<Mesh>();
    std::shared_ptr<Surface> surface6 = std::shared_ptr<Surface>(new Surface(Shader::LoadDefaultShader()));
    surface6->SetColorMap(std::shared_ptr<Texture>(new Texture("mud.png")));
    surface6->SetNormalMap(std::shared_ptr<Texture>(new Texture("boulder_normal.png")));
    bt_box_mesh2->SetSurface(surface6);
    bt_box_mesh2->LoadDefaultCube();
    bt_box2->transform.Translate(glm::vec3(30, 20, 30));
    bt_box2->transform.Scale(glm::vec3(1, 1, 1));
    bt_box2->AddModule<Rigidbody>()->SetCollisionShape(std::shared_ptr<BoxCollider>(new BoxCollider(1.0f, 1.0f, 1.0f)));

    //To ensure gizmos work properly call this just before you start the main loop
    engine.EnableDebugMode();
    engine.Start();
    return 0;
}