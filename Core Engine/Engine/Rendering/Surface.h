#ifndef _SURFACE
#define _SURFACE

class Surface
{
public:
    Surface(){
        
    }
    Surface(std::shared_ptr<Shader> shader){
        this->shader = shader;
    }
    void ApplyTexture(std::shared_ptr<Texture> texture){
        textures.push_back(texture);
    }
    std::shared_ptr<Shader> GetShader(){
        return shader;
    }
    std::vector<std::shared_ptr<Texture>>* GetTextures(){
        return &textures;
    }

private:
    std::shared_ptr<Shader> shader;
    std::vector<std::shared_ptr<Texture>> textures;
};

#endif