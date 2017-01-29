#include "Engine/Core/Core.h"

std::shared_ptr<Core> engine;

class PlayerOneKeyboard : public NonRenderingModule
{
    void Update()
    {
        if (keys_pressed[SDLK_a])
        {
            attached_camera->transform.rotation -= glm::vec3(0, 50, 0) * delta_time;
            attached_camera->transform.position += attached_camera->transform.Right() * delta_time * 5.0f;
        }
        else if (keys_pressed[SDLK_d])
        {
            attached_camera->transform.rotation += glm::vec3(0, 50, 0) * delta_time;
            attached_camera->transform.position -= attached_camera->transform.Right() * delta_time * 5.0f;
        }
        else if (keys_pressed[SDLK_w])
        {
            attached_camera->transform.position += attached_camera->transform.Forward() * delta_time * 5.0f;
        }
        else if (keys_pressed[SDLK_s])
        {
            attached_camera->transform.position -= attached_camera->transform.Forward() * delta_time * 5.0f;
        }

    }
};

class PlayerTwoKeyboard : public NonRenderingModule
{
    void Update()
    {
        if (keys_pressed[SDLK_i])
        {
            attached_camera->transform.rotation -= glm::vec3(0, 50, 0) * delta_time;
            attached_camera->transform.position += attached_camera->transform.Right() * delta_time * 5.0f;
        }
        else if (keys_pressed[SDLK_k])
        {
            attached_camera->transform.rotation += glm::vec3(0, 50, 0) * delta_time;
            attached_camera->transform.position -= attached_camera->transform.Right() * delta_time * 5.0f;
        }
        else if (keys_pressed[SDLK_j])
        {
            attached_camera->transform.position += attached_camera->transform.Forward() * delta_time * 5.0f;
        }
        else if (keys_pressed[SDLK_l])
        {
            attached_camera->transform.position -= attached_camera->transform.Forward() * delta_time * 5.0f;
        }

    }
};

class MyCustomModule2 : public NonRenderingModule
{
    void Update()
    {
        if (keys_pressed[SDLK_UP])
        {
            attached_light->transform.position += glm::vec3(0, 1, 0) * delta_time * 5.0f;
        }
        if (keys_pressed[SDLK_DOWN])
        {
            attached_light->transform.position -= glm::vec3(0, 1, 0) * delta_time * 5.0f;
        }
        if (keys_pressed[SDLK_LEFT])
        {
            attached_light->transform.position -= glm::vec3(1, 0, 0) * delta_time * 5.0f;
        }
        if (keys_pressed[SDLK_RIGHT])
        {
            attached_light->transform.position += glm::vec3(1, 0, 0) * delta_time * 5.0f;
        }
    }
};

class MyGameManager : public Module
{
    bool isFullScreen = false;

    void Input(SDL_Event* e)
    {
        if (e->type == SDL_KEYDOWN)
        {
            if (e->key.keysym.sym == SDLK_TAB)
            {
                isFullScreen=!isFullScreen;
                engine->ChangeResolution(2560,1440, isFullScreen);
            }
            
            else if (e->key.keysym.sym == SDLK_ESCAPE) 
            {
                engine->StopEngine();
            }
        }
        
    }

};

class ControllerInput : public NonRenderingModule
{
    bool isFullScreen = false;

    void Input(SDL_Event* e)
    {
        if(e->type==SDL_CONTROLLERBUTTONDOWN){
            switch(e->cbutton.button)
            {
                case SDL_CONTROLLER_BUTTON_BACK:
                    isFullScreen=!isFullScreen;
                    engine->ChangeResolution(2560,1440, isFullScreen);
                    break;

                case SDL_CONTROLLER_BUTTON_A:
                    attached_camera->transform.position += attached_camera->transform.Forward() * delta_time * 5.0f;
                    break;

                case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                    attached_camera->transform.position -= attached_camera->transform.Forward() * delta_time * 5.0f;
                    break;

                case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                    attached_camera->transform.rotation -= glm::vec3(0, 50, 0) * delta_time;
                    attached_camera->transform.position += attached_camera->transform.Right() * delta_time * 5.0f;
                    break;

                case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                    attached_camera->transform.rotation += glm::vec3(0, 50, 0) * delta_time;
                    attached_camera->transform.position -= attached_camera->transform.Right() * delta_time * 5.0f;
                    break;
            }
        }
    }

    void CheckForControllers()
    {
        //Declare Game controller instance
        SDL_GameController* controller = nullptr;

        //Cycle through Connected Joysticks
        for(int i=0; i<SDL_NumJoysticks(); i++)
        {
            //If any of those happen to be a controller
            if(SDL_IsGameController(i))
            {
                //Assigned that controller to defined instance
                controller = SDL_GameControllerOpen(0);
                if (controller)
                {
                    //Ouput success message to console
                    printf("Controller Found: %s\n", SDL_GameControllerName(controller));
                } 
                break;
            }
        }

    }

    void Update()
    {
        CheckForControllers();
    }

};

int main(int argc, char* args[])
{
    engine = std::shared_ptr<Core>(new Core());

    //Create Camera
    std::shared_ptr<Camera> camera_1 = engine->environments->CreateCamera();
    //Specify how much space the camera takes up in the window
    camera_1->viewport_x = 0;
    camera_1->viewport_y = 0;
    camera_1->viewport_size_x = 1; //Value between 0 and 1. (0.5 is middle of the screen)
    camera_1->viewport_size_y = 0.5;

    //Add Keyboard Input Module
    camera_1->AddModule<PlayerOneKeyboard>();
    //Add Controller Input Module
    camera_1->AddModule<ControllerInput>();

    //Create Camera
    std::shared_ptr<Camera> camera_2 = engine->environments->CreateCamera();
    //Specify how much space the camera takes up in the window
    camera_2->viewport_x = 0;
    camera_2->viewport_y = 0.5;
    camera_2->viewport_size_x = 1; //Value between 0 and 1. (0.5 is middle of the screen)
    camera_2->viewport_size_y = 0.5;

    //Add Keyboard Input Module
    camera_2->AddModule<PlayerTwoKeyboard>();
                                                                                                
    //Create Light
    std::shared_ptr<Light> light1 = engine->environments->CreateLight(Light::LIGHT_TYPE::POINT);
    light1->transform.position = glm::vec3(0, 20, 0);
    light1->light_range = 10.0f;
    light1->brightness = 1.0f;
    light1->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    //Add mycustom Module
    light1->AddModule<MyCustomModule2>();

    //Create a new Cube object
    std::shared_ptr<Entity> myObj = engine->environments->CreateEntity("Cube");
    //Attach Mesh Component So It Is Renders (If no shader is specified it creates a default one)
    std::shared_ptr<Mesh> myMesh = myObj->AddModule<Mesh>();
    //Load obj mesh
    myMesh->LoadModel("monkey3.obj");  // OR myMesh->LoadDefaultCube();
    //Create new Surface (this includes shader and texture)
    std::shared_ptr<Surface> mySurface = std::shared_ptr<Surface>(new Surface("defaultVS.glsl", "defaultFS.glsl"));
    std::shared_ptr<Texture> myTexture = std::shared_ptr<Texture>(new Texture("default.png"));
    mySurface->ApplyTexture(myTexture);
    //Apply Texture and shader to the mesh
    myMesh->ApplySurface(mySurface);

    //Create a new Cube object
    std::shared_ptr<Entity> myObj2 = engine->environments->CreateEntity("Cube");
    myObj2->transform.position = glm::vec3(0, -2.0f, 0.0f);
    //Attach Mesh Component So It Is Renders (If no shader is specified it creates a default one)
    std::shared_ptr<Mesh> myMesh2 = myObj2->AddModule<Mesh>();
    //Load obj mesh
    myMesh2->LoadDefaultCube();
    //Apply Texture and shader to the mesh
    myMesh2->ApplySurface(mySurface);

    //Create A Empty Entity
    std::shared_ptr<Entity> manager = engine->environments->CreateEntity("GameManager");
    manager->AddModule<MyGameManager>();


    //FBO Tests (Renders the camera to an FBO rather then to the screen)
    std::shared_ptr<RendererTexture> rend = std::shared_ptr<RendererTexture>(new RendererTexture(WIDTH, HEIGHT));
    camera_1->SetRenderTarget(rend);

    engine->Start();
    return 0;
}