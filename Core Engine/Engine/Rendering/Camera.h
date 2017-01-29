#ifndef _CAMERA
#define _CAMERA

#include "../Static/Transform.h"
#include "../Modules/NonRenderingModule.h"
#include "RendererTexture.h"

class Camera : public std::enable_shared_from_this<Camera>
{
public:
    float fov;
    float near_clip;
    float far_clip;
    float viewport_x;
    float viewport_y;
    float viewport_size_x;
    float viewport_size_y;
    Transform transform;

    Camera()
    {
        fov = 45.0f;
        near_clip = 0.1f;
        far_clip = 100.0f;
        viewport_x = 0;
        viewport_y = 0;
        viewport_size_x = 1;
        viewport_size_y = 1;
        transform.position = glm::vec3(0.0f, 0.0f, 10.0f);
        transform.rotation = glm::vec3(0.0f, 180.0f, 0.0f);
    }

    void SetRenderTarget(std::shared_ptr<RendererTexture> r){
        render_target = r;
    }

    std::shared_ptr<RendererTexture> GetRenderTarget(){
        return render_target;
    }

    //=======
    // MATHS 
    //=======
    glm::mat4x4 GetProjectionMatrix()
    {
        return glm::perspective(fov, (WIDTH * viewport_size_x) / (HEIGHT * viewport_size_y), near_clip, far_clip);
    }

    glm::mat4x4 GetViewMatrix()
    {
        return lookAt(transform.position, transform.position + transform.Forward(), transform.Up());
    }

    //=========
    // MODULES  
    //=========
    std::vector<std::shared_ptr<NonRenderingModule>> GetModules()
	{
		return modules;
	}
	template <typename T>
	std::shared_ptr<T> AddModule()
	{
		std::shared_ptr<NonRenderingModule> m = std::shared_ptr<T>(new T());
        m->attached_camera = shared_from_this();
		modules.push_back(m);
		return std::dynamic_pointer_cast<T>(m);
	}
	template <typename T>
	std::shared_ptr<T> GetModule()
	{
		for (std::shared_ptr<NonRenderingModule> i : modules)
		{
			if (std::dynamic_pointer_cast<T>(i) != NULL && std::dynamic_pointer_cast<T>(i) != nullptr)
			{
				return std::dynamic_pointer_cast<T>(i);
			}
		}
		return nullptr;
	}
private:
    std::vector<std::shared_ptr<NonRenderingModule>> modules;
    std::shared_ptr<RendererTexture> render_target;
};

#endif