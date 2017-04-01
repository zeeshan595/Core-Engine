#ifndef _CAMERA
#define _CAMERA

class Camera : public Entity
{
public:
    enum VIEW_MODE{
        ORTHOGRAPHIC = 0,
        PERSPECTIVE = 1
    };

    Camera(const char* name);

    void SetViewMode(VIEW_MODE view_mode);
    void SetFOV(float fov);
    void SetOrthoSize(float width, float height);
    void SetNearClip(float clip);
    void SetFarClip(float clip);
    void SetViewport(float x, float y, float width, float height);
    void SetDrawOrder(uint32_t order);

    VIEW_MODE       GetViewMode();
    float           GetFOV();
    void            GetOrthoSize(float &width, float &height);
    float           GetNearClip();
    float           GetFarClip();
    void            GetViewport(float &x, float &y, float &width, float &height);
    uint32_t        GetDrawOrder();

    glm::mat4x4     GetProjectionMatrix();
    glm::mat4x4     GetViewMatrix();

private:
    VIEW_MODE           view_mode                   = PERSPECTIVE;
    float               fov                         = 45.0f;
    glm::vec2           orthographic_size           = glm::vec2(10.0f, 10.0f);
    float               near_clip_plane             = 1.0f;
    float               far_clip_plane              = 1000.0f;
    glm::vec4           viewport                    = glm::vec4(0, 0, 1, 1);
    uint32_t            draw_order                  = 0;

};

#include "Camera.cpp"
#endif