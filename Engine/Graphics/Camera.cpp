Camera::Camera(const char* name) : Entity (name)
{

}

void Camera::SetViewMode(VIEW_MODE view_mode)
{
    this->view_mode = view_mode;
}
void Camera::SetFOV(float fov)
{
    this->fov = fov;
}
void Camera::SetOrthoSize(float width, float height)
{
    this->orthographic_size = glm::vec2(width, height);
}
void Camera::SetNearClip(float clip)
{
    this->near_clip_plane = clip;
}
void Camera::SetFarClip(float clip)
{
    this->far_clip_plane = clip;
}
void Camera::SetViewport(float x, float y, float width, float height)
{
    this->viewport = glm::vec4(x, y, width, height);
}
void Camera::SetDrawOrder(uint32_t order)
{
    this->draw_order = order;
}

Camera::VIEW_MODE   Camera::GetViewMode()
{
    return view_mode;
}
float               Camera::GetFOV()
{
    return fov;
}
void                Camera::GetOrthoSize(float &width, float &height)
{
    width = orthographic_size.x;
    height = orthographic_size.y;
}
float               Camera::GetNearClip()
{
    return near_clip_plane;
}
float               Camera::GetFarClip()
{
    return far_clip_plane;
}
void                Camera::GetViewport(float &x, float &y, float &width, float &height)
{
    x = viewport.x;
    y = viewport.y;
    width = viewport.z;
    height = viewport.w;
}
uint32_t            Camera::GetDrawOrder()
{
    return draw_order;
}

glm::mat4x4         Camera::GetProjectionMatrix()
{
    uint32_t width, height;
    Screen::GetDisplayResolution(width, height);
    if (view_mode == PERSPECTIVE)
        return glm::perspective(fov, (width * viewport.z) / (height * viewport.w), near_clip_plane, far_clip_plane);
    else
        return glm::ortho(-orthographic_size.x * viewport.z, orthographic_size.x * viewport.z, -orthographic_size.y * viewport.w, orthographic_size.y * viewport.w, near_clip_plane, far_clip_plane);
}
glm::mat4x4         Camera::GetViewMatrix()
{
    return lookAt(transform.GetPosition(), transform.GetPosition() + transform.Forward(), transform.Up());
}