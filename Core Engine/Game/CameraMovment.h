#ifndef _CAMERA_MOVMENT
#define _CAMERA_MOVMENT

class CameraMovment : public Module
{
public:
    glm::vec2 border_size;
    glm::vec2 y_range;
    glm::vec2 x_range;
    glm::vec2 z_range;

    void Start(){
        attached_to->transform.position = glm::vec3(50, 20, 50);
        attached_to->transform.rotation = glm::vec3(45,  0,  0);
        border_size = glm::vec2(100, 100);
        y_range = glm::vec2(5, 25);
        x_range = glm::vec2(0, 100);
        z_range = glm::vec2(-10, 90);
    }

    void Update(){
        //Only effect these movments if mouse is inside window
        glm::vec2 window_position = Screen::GetWindowPosition();
        if (Screen::IsWindowFocused())
        if (Input::global_mouse_position.x > window_position.x && Input::global_mouse_position.x < window_position.x + Screen::width){
            if (Input::global_mouse_position.y > window_position.y && Input::global_mouse_position.y < window_position.y + Screen::height){
                //Mouse X,Y movment
                if (Input::mouse_position.x < border_size.x){
                    float multiplier_amount = 0.2 * (border_size.x - Input::mouse_position.x);
                    attached_to->transform.position.x += Time::delta_time * multiplier_amount;
                } else if (Input::mouse_position.x > Screen::width - 100){
                    float multiplier_amount = 0.2 * (border_size.x - (Screen::width - Input::mouse_position.x));
                    attached_to->transform.position.x -= Time::delta_time * multiplier_amount;
                }
                if (Input::mouse_position.y < border_size.y){
                    float multiplier_amount = 0.2 * (border_size.y - Input::mouse_position.y);
                    attached_to->transform.position.z += Time::delta_time * multiplier_amount;
                } else if (Input::mouse_position.y > Screen::height - 100){
                    float multiplier_amount = 0.2 * (border_size.y - (Screen::height - Input::mouse_position.y));
                    attached_to->transform.position.z -= Time::delta_time * multiplier_amount;
                }
            }
        }

        //Mouse Scroll movment
        if (Input::mouse_wheel.y != 0){
            attached_to->transform.position.y += Time::delta_time * -Input::mouse_wheel.y * 100.0f;
        }
        //WASD movment
        if (Input::keys[SDLK_w]){
            attached_to->transform.position.z += Time::delta_time * 20.0f;
        } else if (Input::keys[SDLK_s]) {
            attached_to->transform.position.z -= Time::delta_time * 20.0f;
        } if (Input::keys[SDLK_a]) {
            attached_to->transform.position.x += Time::delta_time * 20.0f;
        } else if (Input::keys[SDLK_d]) {
            attached_to->transform.position.x -= Time::delta_time * 20.0f;
        }

        attached_to->transform.position.y = glm::clamp(attached_to->transform.position.y, y_range.x, y_range.y);
        attached_to->transform.position.x = glm::clamp(attached_to->transform.position.x, x_range.x, x_range.y);
        attached_to->transform.position.z = glm::clamp(attached_to->transform.position.z, z_range.x, z_range.y);
    }
};

#endif