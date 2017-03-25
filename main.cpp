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
    lit->SetLightType(Light::LIGHT_TYPE::POINT);
    lit->transform.SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));

    Camera* cam = Environment::CreateCamera("Camera");
    cam->CreateModule<CameraMovment>();
    cam->transform.SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));

    Entity* obj = Environment::CreateEntity("test object");
    MeshData* mesh = obj->CreateModule<MeshData>();
    mesh->LoadOBJ("monkey3.obj");
    MeshRenderer* renderer = obj->CreateModule<MeshRenderer>();
    obj->transform.SetPosition(glm::vec3(0, 0, 0));

    Entity* my_terrain = Environment::CreateEntity("MyTerrain");
    my_terrain->CreateModule<Terrain>();
    my_terrain->CreateModule<MeshData>();
    MeshRenderer* terrain_renderer = my_terrain->CreateModule<MeshRenderer>();

    Material* material_one = new Material();
    material_one->SetShader(new Shader("default/defaultVS.glsl", "default/defaultFS.glsl"));
    material_one->SetColorMap(new Texture("texture.png"));
    renderer->SetMaterial(material_one);

    Material* material_two = new Material();
    material_two->SetShader(new Shader("default/terrainVS.glsl", "default/terrainFS.glsl"));
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