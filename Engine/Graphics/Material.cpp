Material::Material()
{
    
}

Material::~Material()
{
    
}

void Material::SetShader(Shader* shader)
{
    this->shader = shader;
}
void Material::SetColorMap(Texture* texture)
{
    textures[0] = texture;
}
void Material::SetNormalMap(Texture* texture)
{
    textures[1] = texture;
}
void Material::SetTextures(std::vector<Texture*> textures)
{
    if (textures.size() < 2)
        throw std::runtime_error("Set Textures: The first 2 textures are reserved for color map and normal map. Therefore make sure textures length is grater then or equal to 2");

    this->textures = textures;
}
Shader*                   Material::GetShader()
{
    return shader;
}
std::vector<Texture*>*    Material::GetTextures()
{
    return &textures;
}