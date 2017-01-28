#ifndef _NON_RENDERING_MODULE
#define _NON_RENDERING_MODULE

class Light;
class Camera;
class NonRenderingModule
{
public:
    std::shared_ptr<Camera> attached_camera;
    std::shared_ptr<Light> attached_light;

    virtual void Update(){}
    virtual void Input(SDL_Event* e){}
};

#endif