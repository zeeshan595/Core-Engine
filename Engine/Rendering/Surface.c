std::shared_ptr<Surface> Surface::LoadDefaultSurface()
{
    return std::shared_ptr<Surface>(new Surface(Shader::LoadDefaultShader()));
}

Surface::Surface(std::shared_ptr<Shader> shader)
{
    this->shader = shader;
    textures.resize(3);
    textures[0] = std::shared_ptr<Texture>(new Texture("default/texture.png"));
    textures[1] = std::shared_ptr<Texture>(new Texture("default/normal.png"));
    textures[2] = std::shared_ptr<Texture>(new Texture("default/specular.png"));
}

void Surface::SetColorMap(std::shared_ptr<Texture> texture)
{
    textures[0] = texture;
}

void Surface::SetNormalMap(std::shared_ptr<Texture> texture)
{
    textures[1] = texture;
}

void Surface::SetSpecularMap(std::shared_ptr<Texture> texture)
{
    textures[2] = texture;
}

void Surface::AddAdditionalTexture(std::shared_ptr<Texture> texture)
{
    if (textures.size() == 20){
        std::cout << "Maximum of 20 textures limited to 1 shader" << std::endl;
        return;
    }
    textures.push_back(texture);
}

std::shared_ptr<Shader> Surface::GetShader()
{
    return shader;
}

std::vector<std::shared_ptr<Texture>>* Surface::GetTextures()
{
    return &textures;
}