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
        this->texture = texture;
    }
    std::shared_ptr<Shader> GetShader(){
        return shader;
    }
    std::shared_ptr<Texture> GetTexture(){
        return texture;
    }

private:
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Texture> texture;
};

#endif