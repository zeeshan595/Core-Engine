#include "Engine/Common.h"

class CameraMovment : public Module
{
public:

    float rotation_x = 0;
    float rotation_y = 0;
    glm::vec3 position;

    void Update(){
        if (Input::GetKey(SDLK_w))
            position += entity->transform.Forward() * 20.0f * Time::delta_time;
        else if (Input::GetKey(SDLK_s))
            position -= entity->transform.Forward() * 20.0f * Time::delta_time;

        if (Input::GetKey(SDLK_a))
            position += entity->transform.Right() * 20.0f * Time::delta_time;
        else if (Input::GetKey(SDLK_d))
            position -= entity->transform.Right() * 20.0f * Time::delta_time;

        glm::vec2 mouse_delta = Input::GetMouseDelta();
        rotation_x += mouse_delta.y * Time::delta_time * 5.0f;
        rotation_y -= mouse_delta.x * Time::delta_time * 5.0f;

        entity->transform.Rotate(glm::vec3(rotation_x, rotation_y, 0));
        entity->transform.SetPosition(position);
    }
};

int main(int argc, char* args[])
{
    //Setup Window
    Screen::SetWindowTitle("The Car Game");
    Screen::SetResolution(1920, 1080, false);
    Screen::SetScreenPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    //Create Scene
    Environment* scene = Environment::CreateEnvironment("default");
    Environment::SetEnvironment(scene, false);

    //Skybox
    CubeTexture* skybox_texture = new CubeTexture("default/skybox_day.png", "default/skybox_day.png", "default/skybox_day.png", "default/skybox_day.png", "default/skybox_day.png", "default/skybox_day.png");
    Shader* skybox_shader = new Shader("default/skyboxVS.glsl", "default/skyboxFS.glsl");
    Environment::SetSkybox(new Skybox(skybox_texture, skybox_shader));

    //Light
    Light* lit = Environment::CreateLight("Light");
    lit->SetLightType(Light::LIGHT_TYPE::DIRECTIONAL);
    lit->transform.Rotate(glm::vec3(-120, 0, 0));

    //Camera
    Camera* cam = Environment::CreateCamera("Camera");
    cam->CreateModule<CameraMovment>();
    cam->transform.SetPosition(glm::vec3(0.0f, 21.0f, 30.0f));
    cam->transform.Rotate(glm::vec3(0.0f, 3.14f, 0.0f));

    //Objects
    Entity* monkey_obj = Environment::CreateEntity("monkey_obj");
    MeshData* mesh = monkey_obj->CreateModule<MeshData>();
    mesh->LoadOBJ("dragon.obj");
    MeshRenderer* monkey_renderer = monkey_obj->CreateModule<MeshRenderer>();
    monkey_obj->transform.SetPosition(glm::vec3(0, 10, 0));
    monkey_obj->transform.Rotate(glm::vec3(0, 0, 0));

    Entity* my_terrain = Environment::CreateEntity("MyTerrain");
    my_terrain->CreateModule<Terrain>();
    my_terrain->CreateModule<MeshData>();
    MeshRenderer* terrain_renderer = my_terrain->CreateModule<MeshRenderer>();

    //Setup Shaders
    Shader* boulder_shader              = new Shader("default/defaultVS.glsl", "default/defaultFS.glsl");
    Shader* terrain_shader              = new Shader("Default/terrainVS.glsl", "Default/terrainFS.glsl");

    //Setup Textures
    Texture* boulder_texture            = new Texture("boulder.png");
    Texture* boulder_texture_normal     = new Texture("boulder_normal.png");
    Texture* terrain_texture_blend_map  = new Texture("blend_map.png");
    Texture* terrain_texture_grass      = new Texture("grassy2.png");
    Texture* terrain_texture_flowers    = new Texture("grassFlowers.png");
    Texture* terrain_texture_mud        = new Texture("mud.png");
    Texture* terrain_texture_path       = new Texture("path.png");

    //Setup Materials
    Material* material_one = new Material();
    material_one->SetShader(boulder_shader);
    material_one->SetTextures({
        boulder_texture,
        boulder_texture_normal
    });
    monkey_renderer->SetMaterial(material_one);

    Material* material_two = new Material();
    material_two->SetShader(terrain_shader);
    material_two->SetTextures({
        terrain_texture_blend_map,
        terrain_texture_grass,
        terrain_texture_flowers,
        terrain_texture_mud,
        terrain_texture_path
    });
    material_two->SetLightReflectivity(0.0f);
    terrain_renderer->SetMaterial(material_two);

    engine.Start();
    //CleanUp
    delete skybox_texture;
    delete skybox_shader;
    delete boulder_shader;
    delete boulder_texture;
    delete boulder_texture_normal;
    delete terrain_shader;
    delete terrain_texture_blend_map;
    delete terrain_texture_grass;
    delete terrain_texture_flowers;
    delete terrain_texture_mud;
    delete terrain_texture_path;
    delete material_one;
    delete material_two;
    Environment::DestroyEnvironment(scene);

    return 0;
}