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

    static Shader*                  player_shader;
    static Texture*                 player_texture_map;
    static Texture*                 player_normal_map;
    static Material*                player_material;

    static Shader*                  building_shader;
    static Texture*                 building_texture_map;
    static Texture*                 building_normal_map;
    static Material*                building_material;

    static void SetupResources()
    {
        skybox_texture  = new CubeTexture("mountains/right.png", "mountains/left.png", "mountains/up.png", 
        "mountains/down.png", "mountains/bk.png", "mountains/front.png");
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

        player_shader          = new Shader("Default/defaultVS.glsl", "Default/defaultFS.glsl");
        player_texture_map     = new Texture("default.png");
        player_normal_map      = new Texture("Default/normal.png");
        player_material        = new Material();
        player_material->SetShader(player_shader);
        player_material->SetTextures({ player_texture_map, player_normal_map });

        building_shader          = new Shader("Default/defaultVS.glsl", "Default/defaultFS.glsl");
        building_texture_map     = new Texture("default.png");
        building_normal_map      = new Texture("HouseLong.jpg");
        building_material        = new Material();
        building_material->SetShader(building_shader);
        building_material->SetTextures({ building_texture_map, building_normal_map });
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

        delete player_shader;              player_shader          = NULL;
        delete player_texture_map;         player_texture_map     = NULL;
        delete player_normal_map;          player_normal_map      = NULL;
        delete player_material;            player_material        = NULL;

        delete building_shader;            building_shader = NULL;
        delete building_texture_map;       building_texture_map = NULL;
        delete building_normal_map;        building_normal_map = NULL;
        delete building_material;          building_material = NULL;
    }
};

CubeTexture*                GameResources::skybox_texture               = NULL;
Shader*                     GameResources::skybox_shader                = NULL;
Skybox*                     GameResources::skybox                       = NULL;
Shader*                     GameResources::terrain_shader               = NULL;
std::vector<Texture*>       GameResources::terrain_textures;
Material*                   GameResources::terrain_material             = NULL;
Shader*                     GameResources::player_shader                   = NULL;
Texture*                    GameResources::player_texture_map              = NULL;
Texture*                    GameResources::player_normal_map               = NULL;
Material*                   GameResources::player_material                 = NULL;

Shader*                     GameResources::building_shader                   = NULL;
Texture*                    GameResources::building_texture_map              = NULL;
Texture*                    GameResources::building_normal_map               = NULL;
Material*                   GameResources::building_material                 = NULL;


#endif