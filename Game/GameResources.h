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

    static Shader*                  radio_shader;
    static Texture*                 radio_texture_map;
    static Texture*                 radio_normal_map;
    static Material*                radio_material;

    static Shader*                  crate_shader;
    static Texture*                 crate_texture_map;
    static Texture*                 crate_normal_map;
    static Material*                crate_material;

    static Shader*                  crate_shader2;
    static Texture*                 crate_texture_map2;
    static Texture*                 crate_normal_map2;
    static Material*                crate_material2;

    static void SetupResources()
    {
        skybox_texture  = new CubeTexture("default/texture.png", "default/texture.png", "mountains/up.png", 
        "mountains/down.png", "default/texture.png", "default/texture.png");
        skybox_shader   = new Shader("Default/skyboxVS.glsl", "Default/skyboxFS.glsl");
        skybox          = new Skybox(skybox_texture, skybox_shader);

        terrain_shader      = new Shader("Default/terrainVS.glsl", "Default/terrainFS.glsl");
        terrain_textures    = {
            new Texture("blend_map.png"),
            new Texture("grassy2.png"),
            new Texture("dirt.jpg"),
            new Texture("mud.png"),
            new Texture("path.png")
        };
        terrain_material    = new Material();
        terrain_material->SetShader(terrain_shader);
        terrain_material->SetTextures(terrain_textures);
        terrain_material->SetLightReflectivity(0.0f);

        player_shader          = new Shader("Default/defaultVS.glsl", "Default/defaultFS.glsl");
        player_texture_map     = new Texture("swat_diff.png");
        player_normal_map      = new Texture("swat_normal.png");
        player_material        = new Material();
        player_material->SetShader(player_shader);
        player_material->SetTextures({ player_texture_map, player_normal_map });

        building_shader          = new Shader("Default/defaultVS.glsl", "Default/defaultFS.glsl");
        building_texture_map     = new Texture("cloth_roof.png");
        building_normal_map      = new Texture("default.png");
        building_material        = new Material();
        building_material->SetShader(building_shader);
        building_material->SetTextures({ building_texture_map, building_normal_map });

        radio_shader          = new Shader("Default/defaultVS.glsl", "Default/defaultFS.glsl");
        radio_texture_map     = new Texture("radio_diffuse.png");
        radio_normal_map      = new Texture("radio_NRM.png");
        radio_material        = new Material();
        radio_material->SetShader(building_shader);
        radio_material->SetTextures({ radio_texture_map, radio_normal_map });

        crate_shader          = new Shader("Default/defaultVS.glsl", "Default/defaultFS.glsl");
        crate_texture_map     = new Texture("Crate01.png");
        crate_normal_map      = new Texture("Crate01_NRM.png");
        crate_material        = new Material();
        crate_material->SetShader(building_shader);
        crate_material->SetTextures({ crate_texture_map, crate_normal_map });

        crate_shader2          = new Shader("Default/defaultVS.glsl", "Default/defaultFS.glsl");
        crate_texture_map2     = new Texture("Crate02.png");
        crate_normal_map2      = new Texture("Crate02_NRM.png");
        crate_material2       = new Material();
        crate_material2->SetShader(building_shader);
        crate_material2->SetTextures({ crate_texture_map2, crate_normal_map2 });

        
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

Shader*                     GameResources::radio_shader                   = NULL;
Texture*                    GameResources::radio_texture_map              = NULL;
Texture*                    GameResources::radio_normal_map               = NULL;
Material*                   GameResources::radio_material                 = NULL;

Shader*                     GameResources::crate_shader                   = NULL;
Texture*                    GameResources::crate_texture_map              = NULL;
Texture*                    GameResources::crate_normal_map               = NULL;
Material*                   GameResources::crate_material                 = NULL;

Shader*                     GameResources::crate_shader2                   = NULL;
Texture*                    GameResources::crate_texture_map2              = NULL;
Texture*                    GameResources::crate_normal_map2               = NULL;
Material*                   GameResources::crate_material2                 = NULL;


#endif