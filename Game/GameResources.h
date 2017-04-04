#ifndef _RESOURCES
#define _RESOURCES

class GameResources
{
public:
    static bool                     mute_sounds;

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

    static Texture*                 stall_texture;
    static Material*                stall_material;

    static Texture*                 dragon_texture;
    static Material*                dragon_material;

    static Texture*                 tree_texture;
    static Material*                tree_material;

    static void SetupResources()
    {
        skybox_texture  = new CubeTexture("left.png", "right.png", "top.png", "bottom.png", "front.png", "back.png");
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

        stall_texture       = new Texture("stall.png");
        stall_material      = new Material();
        stall_material->SetShader(car_shader);
        stall_material->SetTextures({ stall_texture, car_normal_map });

        dragon_texture      = new Texture("dragon.png");
        dragon_material     = new Material();
        dragon_material->SetShader(car_shader);
        dragon_material->SetTextures({ dragon_texture, car_normal_map });
        dragon_material->SetLightReflectivity(0.0f);

        tree_texture        = new Texture("tree.png");
        tree_material       = new Material();
        tree_material->SetShader(car_shader);
        tree_material->SetTextures({ tree_texture, car_normal_map });
        tree_material->SetLightReflectivity(0.1f);
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

        delete stall_texture;           stall_texture       = NULL;
        delete stall_material;          stall_material      = NULL;

        delete dragon_texture;          dragon_texture       = NULL;
        delete dragon_material;         dragon_material      = NULL;

        delete tree_texture;            tree_texture        = NULL;
        delete tree_material;           tree_material       = NULL;
    }
};

bool                        GameResources::mute_sounds                  = false;

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

Texture*                    GameResources::stall_texture                = NULL;
Material*                   GameResources::stall_material               = NULL;

Texture*                    GameResources::dragon_texture               = NULL;
Material*                   GameResources::dragon_material              = NULL;

Texture*                    GameResources::tree_texture                 = NULL;
Material*                   GameResources::tree_material                = NULL;

#endif