#ifndef _CAMERA_MOVMENT
#define _CAMERA_MOVMENT

class CameraMovment : public Module
{
public:

    void Start(){
        attached_to->transform.position = glm::vec3(50, 20, 50);
        attached_to->transform.rotation = glm::vec3(45,  0,  0);
        Input::LockCursor(true);
    }

    void Update(){
        if (Input::keys[SDLK_w])
            attached_to->transform.position += attached_to->transform.Forward() * 20.0f * Time::delta_time;
        else if (Input::keys[SDLK_s])
            attached_to->transform.position -= attached_to->transform.Forward() * 20.0f * Time::delta_time;

        if (Input::keys[SDLK_a])
            attached_to->transform.position += attached_to->transform.Right() * 20.0f * Time::delta_time;
        else if (Input::keys[SDLK_d])
            attached_to->transform.position -= attached_to->transform.Right() * 20.0f * Time::delta_time;

        attached_to->transform.rotation.y -= Input::mouse_delta.x * Time::delta_time;
        attached_to->transform.rotation.x += Input::mouse_delta.y * Time::delta_time;

        if (Input::mouse_down[SDL_BUTTON_LEFT]){
            Input::LockCursor(true);
        }
        if (Input::keys_down[SDLK_ESCAPE]){
            Input::LockCursor(false);
        }
    }
};

#endif