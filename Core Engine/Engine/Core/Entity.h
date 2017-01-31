#ifndef _ENTITY
#define _ENTITY

class Entity: public std::enable_shared_from_this<Entity>
{
public:
    std::string name;
	Transform transform;
	int layer;

    Entity(std::string n){
        name = n;
		layer = 0;
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