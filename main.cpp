#include "Engine/Common.h"

int main(int argc, char* args[])
{
    //Setup Window
    Screen::SetWindowTitle("The Car Game");
    Screen::SetResolution(1920, 1080, false);
    Screen::SetScreenPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    //Create Scene
    Environment* scene = Environment::CreateEnvironment("Default");
    Environment::SetEnvironment(scene, false);

    //Skybox
    CubeTexture* skybox_texture = new CubeTexture("Default/skybox_day.png", "Default/skybox_day.png", "Default/skybox_day.png", "Default/skybox_day.png", "Default/skybox_day.png", "Default/skybox_day.png");
    Shader* skybox_shader = new Shader("Default/skyboxVS.glsl", "Default/skyboxFS.glsl");
    Environment::SetSkybox(new Skybox(skybox_texture, skybox_shader));

    //Light
    Light* lit = Environment::CreateLight("Light");
    lit->SetLightType(Light::LIGHT_TYPE::DIRECTIONAL);
    lit->transform.Rotate(glm::vec3(-120, 0, 0));

    //Camera
    Camera* cam = Environment::CreateCamera("Camera");
    cam->transform.SetPosition(glm::vec3(0.0f, 21.0f, 30.0f));
    cam->transform.Rotate(glm::vec3(0.0f, 3.14f, 0.0f));

    //UI
    Entity* UI_OBJ = Environment::CreateEntity("UI Object");
    UI_OBJ->transform.SetPosition(glm::vec3(-2, -2, 0));
    UI_OBJ->transform.SetSize(glm::vec3(0.5f, 0.5f, 1));
    UI* ui_module = UI_OBJ->CreateModule<UI>();
    Shader* ui_shader = new Shader("Default/uiVS.glsl", "Default/uiFS.glsl");
    Texture* ui_texture = new Texture("texture.png");
    ui_module->SetShader(ui_shader);
    ui_module->SetTexture(ui_texture);

    engine.Start();
    //CleanUp
    delete skybox_texture;
    delete skybox_shader;
    delete ui_texture;
    delete ui_shader;

    return 0;
}