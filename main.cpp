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
        rotation_x += mouse_delta.y * Time::delta_time * 15.0f;
        rotation_y -= mouse_delta.x * Time::delta_time * 15.0f;

        entity->transform.Rotate(glm::vec3(rotation_x, rotation_y, 0));
        entity->transform.SetPosition(position);
    }
};

int main(int argc, char* args[])
{
    Screen::SetWindowTitle("The Car Game");
    Screen::SetResolution(1920, 1080, false);
    Screen::SetScreenPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    Environment* scene = Environment::CreateEnvironment("default");
    Environment::SetSkybox(new Skybox());

    Light* lit = Environment::CreateLight("Light");
    lit->SetLightType(Light::LIGHT_TYPE::DIRECTIONAL);
    lit->transform.Rotate(glm::vec3(-120, 0, 0));

    Camera* cam = Environment::CreateCamera("Camera");
    cam->CreateModule<CameraMovment>();
    cam->transform.SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));

    Entity* monkey_obj = Environment::CreateEntity("monkey_obj");
    MeshData* mesh = monkey_obj->CreateModule<MeshData>();
    mesh->SetMeshData(Plane::vertices, Plane::indices);
    MeshRenderer* monkey_renderer = monkey_obj->CreateModule<MeshRenderer>();
    monkey_obj->transform.SetPosition(glm::vec3(0, 10, 0));

    Entity* my_terrain = Environment::CreateEntity("MyTerrain");
    my_terrain->CreateModule<Terrain>();
    my_terrain->CreateModule<MeshData>();
    MeshRenderer* terrain_renderer = my_terrain->CreateModule<MeshRenderer>();

    Material* material_one = new Material();
    material_one->SetShader(new Shader("Default/defaultVS.glsl", "Default/defaultFS.glsl"));
    material_one->SetTextures({
        new Texture("boulder.png"),
        new Texture("boulder_normal.png")
    });
    monkey_renderer->SetMaterial(material_one);

    Material* material_two = new Material();
    material_two->SetShader(new Shader("Default/terrainVS.glsl", "Default/terrainFS.glsl"));
    material_two->SetTextures({
        new Texture("blend_map.png"),
        new Texture("grassy2.png"),
        new Texture("grassFlowers.png"),
        new Texture("mud.png"),
        new Texture("path.png")
    });
    terrain_renderer->SetMaterial(material_two);

    engine.Start();
    Environment::DestroyEnvironment(scene);
    return 0;
}