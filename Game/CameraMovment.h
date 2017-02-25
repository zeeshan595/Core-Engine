#ifndef _CAMERA_MOVMENT
#define _CAMERA_MOVMENT

class CameraMovment : public Module
{
public:

    float rotation_x = 0;
    float rotation_y = 0;
    glm::vec3 position;

    void Start(){
        position = glm::vec3(50, 20, 50);
        //attached_to->transform.rotation = glm::vec3(45,  0,  0);
        Input::LockCursor(true);
    }

    void Update(){
        
        if (Input::keys[SDLK_w])
            position += attached_to->transform.Forward() * 20.0f * Time::delta_time;
        else if (Input::keys[SDLK_s])
            position -= attached_to->transform.Forward() * 20.0f * Time::delta_time;

        if (Input::keys[SDLK_a])
            position += attached_to->transform.Right() * 20.0f * Time::delta_time;
        else if (Input::keys[SDLK_d])
            position -= attached_to->transform.Right() * 20.0f * Time::delta_time;

        rotation_x += Input::mouse_delta.y * Time::delta_time * 1;
        rotation_y -= Input::mouse_delta.x * Time::delta_time * 1;

        attached_to->transform.Rotate(glm::vec3(rotation_x, rotation_y, 0));

        if (Input::mouse_down[SDL_BUTTON_LEFT]){
            Input::LockCursor(true);
        }
        if (Input::keys_down[SDLK_ESCAPE]){
            Input::LockCursor(false);
        }

        attached_to->transform.Translate(position);
    }
};

#endif