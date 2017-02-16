#ifndef _CAMERA
#define _CAMERA

class Camera : public Entity
{
public:
    enum VIEW_MODE{
        ORTHOGRAPHIC = 0,
        PERSPECTIVE = 1
    };

    VIEW_MODE view_mode;
    float fov;
    glm::vec2 orthographic_size;
    float near_clip_plane;
    float far_clip_plane;
    glm::vec4 viewport;
    int draw_order;

    Camera(std::string name) : Entity(name){
        view_mode = PERSPECTIVE;
        fov = 45.0f;
        orthographic_size = glm::vec2(10.0f, 10.0f);
        near_clip_plane = 0.01f;
        far_clip_plane = 1000.0f;
        viewport = glm::vec4(0, 0, 1, 1);
        draw_order = 0;
    }

    glm::mat4x4 GetProjectionMatrix()
    {
        if (view_mode == PERSPECTIVE)
            return glm::perspective(fov, (Screen::width * viewport.z) / (Screen::height * viewport.w), near_clip_plane, far_clip_plane);
        else
            return glm::ortho(-orthographic_size.x * viewport.z, orthographic_size.x * viewport.z, -orthographic_size.y * viewport.w, orthographic_size.y * viewport.w, near_clip_plane, far_clip_plane);
    }

    glm::mat4x4 GetViewMatrix()
    {
        return lookAt(transform.position, transform.position + transform.Forward(), transform.Up());
    }

    //Modules
    std::vector<std::shared_ptr<Module>> GetModules(){
		return modules;
	}
	template <typename T>
	std::shared_ptr<T> AddModule(){
		std::shared_ptr<Module> m = std::shared_ptr<T>(new T());
		m->attached_to = shared_from_this();
		modules.push_back(m);
		return std::dynamic_pointer_cast<T>(m);
	}
	template <typename T>
	std::shared_ptr<T> GetModule(){
		for (std::shared_ptr<Module> i : modules)
		{
			if (std::dynamic_pointer_cast<T>(i) != NULL && std::dynamic_pointer_cast<T>(i) != nullptr)
			{
				return std::dynamic_pointer_cast<T>(i);
			}
		}
		return nullptr;
	}
    //For sorting cameras using draw order
    bool operator<(const Camera other)
    {
        return draw_order < other.draw_order;
    }

private:
    std::vector<std::shared_ptr<Module>> modules;
};

#endif