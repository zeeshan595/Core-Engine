#ifndef _LIGHT
#define _LIGHT

#include "../Static/Transform.h"
#include "../Modules/NonRenderingModule.h"

class Light : public std::enable_shared_from_this<Light>
{
public:
    enum LIGHT_TYPE{
        POINT = 0,
        DIRECTIONAL = 1
    };

    glm::vec4 color;
    float brightness;
    float light_range;
    Transform transform;
    LIGHT_TYPE light_type;

    Light(LIGHT_TYPE type)
    {
        color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        brightness = 1.0f;
        light_range = 10.0f;
        transform = Transform();
        light_type = type;
    }

	//Modules
    std::vector<std::shared_ptr<NonRenderingModule>> GetModules()
	{
		return modules;
	}
	template <typename T>
	std::shared_ptr<T> AddModule()
	{
		std::shared_ptr<NonRenderingModule> m = std::shared_ptr<T>(new T());
		m->attached_light = shared_from_this();
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
};

#endif