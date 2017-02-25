Terrain::Terrain()
{
    max_height      = 10.0f;
    terrain_size_x  = 100.0f;
    terrain_size_z  = 100.0f;
    density         = 1.0f;
    blend_map       = "blend_map.png";
    height_map      = "height_map.png";
    tile_texture0 = "grassy2.png";
    tile_texture1 = "grassFlowers.png";
    tile_texture2 = "mud.png";
    tile_texture3 = "path.png";
    terrain_shader = std::shared_ptr<Shader>(new Shader("default/terrainVS.glsl", "default/terrainFS.glsl"));
}

float Terrain::TerrainHeight(float world_x, float world_z)
{
    glm::vec3 my_position = attached_to->transform.GetPosition();
    float terrain_x = world_x - my_position.x;
    float terrain_z = world_z - my_position.z;
    int grid_x = (int)(terrain_x / density);
    int grid_z = (int)(terrain_z / density);

    if (grid_x >= (heights.size() - 1) || grid_z >= (heights[0].size() - 1) || grid_x < 0 || grid_z < 0)
        return 0;
    
    float xCoord = fmod(terrain_x, density) / density;
    float zCoord = fmod(terrain_z, density) / density;
    float answer = 0;
    if (xCoord <= (1 - zCoord))
    {
        answer = barryCentric(
            glm::vec3(0, heights[grid_x    ][grid_z    ], 0),
            glm::vec3(1, heights[grid_x + 1][grid_z    ], 0),
            glm::vec3(0, heights[grid_x    ][grid_z + 1], 1),
            glm::vec2(xCoord, zCoord)
        );
    }
    else
    {
        answer = barryCentric(
            glm::vec3(1, heights[grid_x + 1][grid_z    ], 0),
            glm::vec3(1, heights[grid_x + 1][grid_z + 1], 1),
            glm::vec3(0, heights[grid_x    ][grid_z + 1], 1),
            glm::vec2(xCoord, zCoord)
        );
    }
    return answer;
}

TerrainCollider::TerrainData Terrain::GetTerrainCollisionInfo()
{
    if (heights.size() == 0)
    {
        std::cout << "ERROR: please create terrain before getting collision information" << std::endl;
        return {  };
    }
    float x_size = terrain_size_x * density;
    float z_size = terrain_size_z * density;
    float* heights_data = GetHeightsData();
    return { x_size, z_size, heights_data, max_height };
}

float* Terrain::GetHeightsData()
{
    float* hightfield_data = new float[terrain_size_x * terrain_size_z];
    for (int i = 0; i < terrain_size_z; i++){
        for (int j = 0; j < terrain_size_x; j++){
            hightfield_data[(i * terrain_size_x) + j] = heights[j][i];
        }
    }
    return hightfield_data;
}

void Terrain::CreateTerrain()
{
    std::shared_ptr<Mesh> attached_mesh = attached_to->GetModule<Mesh>();
    if (attached_mesh == nullptr){
        attached_mesh = attached_to->AddModule<Mesh>();
    }
    std::shared_ptr<Surface> mySurface = std::shared_ptr<Surface>(new Surface(terrain_shader));
    mySurface->SetColorMap(std::shared_ptr<Texture>(new Texture(blend_map)));
    mySurface->SetNormalMap(std::shared_ptr<Texture>(new Texture(tile_texture0)));
    mySurface->AddAdditionalTexture(std::shared_ptr<Texture>(new Texture(tile_texture1)));
    mySurface->AddAdditionalTexture(std::shared_ptr<Texture>(new Texture(tile_texture2)));
    mySurface->AddAdditionalTexture(std::shared_ptr<Texture>(new Texture(tile_texture3)));
    attached_mesh->SetSurface(mySurface);
    
    height_map_surface = Texture::LoadImage(height_map);

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    vertices.resize((terrain_size_x + 1) * (terrain_size_z + 1));
    heights.resize((terrain_size_x + 1));

    for (int x = 0; x < terrain_size_x + 1; x++){
        heights[x].resize((terrain_size_z + 1));
        for (int y = 0; y < terrain_size_z + 1; y++){
            float uv_x = (float)x / (float)terrain_size_x;
            float uv_y = (float)y / (float)terrain_size_z;
            float height = GetPixelColor((int)(height_map_surface->w * uv_x), (int)(height_map_surface->h * uv_y));
            heights[x][y] = height;
            vertices[GetVertexPosition(x, y)] = {
                glm::vec3(density * x, height, density * y),
                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                glm::vec2(uv_x, uv_y),
                CalculateNormal((int)(height_map_surface->w * uv_x), (int)(height_map_surface->h * uv_y))
            };
        }
    }

    SDL_FreeSurface(height_map_surface);

    for (int x = 0; x < terrain_size_x; x++){
        for (int y = 0; y < terrain_size_z; y++){
            indices.push_back(GetVertexPosition(x, y));
            indices.push_back(GetVertexPosition(x + 1, y + 1));
            indices.push_back(GetVertexPosition(x + 1, y));

            indices.push_back(GetVertexPosition(x, y));
            indices.push_back(GetVertexPosition(x, y + 1));
            indices.push_back(GetVertexPosition(x + 1, y + 1));
        }
    }

    attached_mesh->CreateMesh(vertices, indices);
}

glm::vec3 Terrain::CalculateNormal(int x, int z)
{
    float heightL = GetPixelColor(x-1, z  );
    float heightR = GetPixelColor(x+1, z  );
    float heightD = GetPixelColor(x  , z-1);
    float heightU = GetPixelColor(x  , z+1);

    glm::vec3 normal = glm::vec3(heightL - heightR, 0.5f, heightD - heightU);
    return glm::normalize(normal);
}

float Terrain::GetPixelColor(int x, int y)
{
    if (x < 0 || x > height_map_surface->w || y < 0 || y > height_map_surface->h)
        return 0;

    Uint8 r, g, b;
    SDL_GetRGB(GetPixel(x, y), height_map_surface->format, &r, &g, &b);
    float height = r * g * b;
    height /= MAX_PIXEL_COLOUR / 2.0f;
    height *= max_height;
    return height;
}

Uint32 Terrain::GetPixel(int x, int y)
{
    int bpp = height_map_surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)height_map_surface->pixels + y * height_map_surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

int Terrain::GetVertexPosition(int x, int y)
{
    return x + ((terrain_size_x + 1) * y);
}

float Terrain::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}