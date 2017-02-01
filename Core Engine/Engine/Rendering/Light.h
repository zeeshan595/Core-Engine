#ifndef _LIGHT
#define _LIGHT

class Light : public Entity
{
public:
    enum LIGHT_TYPE{
        POINT = 0,
        DIRECTIONAL = 1
    };

    LIGHT_TYPE type;
    glm::vec4 color;
    float brightness;
    float light_range;

    Light(std::string name) : Entity(name)
    {
        color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        brightness = 1.0f;
        light_range = 10.0f;
        type = DIRECTIONAL;
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
private:
    std::vector<std::shared_ptr<Module>> modules;
};

#endif