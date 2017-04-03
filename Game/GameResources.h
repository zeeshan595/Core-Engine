#ifndef _RESOURCES
#define _RESOURCES

class GameResources
{
public:
    static CubeTexture*             skybox_texture;
    static Shader*                  skybox_shader;
    static Skybox*                  skybox;
    
    static Shader*                  terrain_shader;
    static std::vector<Texture*>    terrain_textures;
    static Material*                terrain_material;

    static Shader*                  car_shader;
    static Texture*                 car_texture_map;
    static Texture*                 car_normal_map;
    static Material*                car_material;

    static void SetupResources()
    {
        skybox_texture  = new CubeTexture("Default/skybox_day.png", "Default/skybox_day.png", "Default/skybox_day.png", "Default/skybox_day.png", "Default/skybox_day.png", "Default/skybox_day.png");
        skybox_shader   = new Shader("Default/skyboxVS.glsl", "Default/skyboxFS.glsl");
        skybox          = new Skybox(skybox_texture, skybox_shader);

        terrain_shader      = new Shader("Default/terrainVS.glsl", "Default/terrainFS.glsl");
        terrain_textures    = {
            new Texture("blend_map.png"),
            new Texture("grassy2.png"),
            new Texture("grassFlowers.png"),
            new Texture("mud.png"),
            new Texture("path.png")
        };
        terrain_material    = new Material();
        terrain_material->SetShader(terrain_shader);
        terrain_material->SetTextures(terrain_textures);
        terrain_material->SetLightReflectivity(0.0f);

        car_shader          = new Shader("Default/defaultVS.glsl", "Default/defaultFS.glsl");
        car_texture_map     = new Texture("car.png");
        car_normal_map      = new Texture("Default/normal.png");
        car_material        = new Material();
        car_material->SetShader(car_shader);
        car_material->SetTextures({ car_texture_map, car_normal_map });
    }

    static void DestroyResources()
    {
        delete skybox_texture;          skybox_texture      = NULL;
        delete skybox_shader;           skybox_shader       = NULL;
        delete skybox;                  skybox              = NULL;

        delete terrain_shader;          terrain_shader      = NULL;
        for (uint32_t i = 0; i < terrain_textures.size(); i++)
            delete terrain_textures[i];
        terrain_textures.clear();
        delete terrain_material;        terrain_material    = NULL;

        delete car_shader;              car_shader          = NULL;
        delete car_texture_map;         car_texture_map     = NULL;
        delete car_normal_map;          car_normal_map      = NULL;
        delete car_material;            car_material        = NULL;
    }
};

CubeTexture*                GameResources::skybox_texture               = NULL;
Shader*                     GameResources::skybox_shader                = NULL;
Skybox*                     GameResources::skybox                       = NULL;
Shader*                     GameResources::terrain_shader               = NULL;
std::vector<Texture*>       GameResources::terrain_textures;
Material*                   GameResources::terrain_material             = NULL;
Shader*                     GameResources::car_shader                   = NULL;
Texture*                    GameResources::car_texture_map              = NULL;
Texture*                    GameResources::car_normal_map               = NULL;
Material*                   GameResources::car_material                 = NULL;

#endif