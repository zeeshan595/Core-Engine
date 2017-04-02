void Terrain::Start()
{
    //Compute Vertices & Heights
    SDL_Surface* hight_map_surface = GetHeightMapImage();
    std::vector<Vertex> vertices(terrain_size_x * terrain_size_z);
    heights.resize(terrain_size_x);
    for (uint32_t x = 0; x < terrain_size_x; x++)
    {
        heights[x].resize(terrain_size_z);
        for (uint32_t z = 0; z < terrain_size_z; z++)
        {
            float uv_x = (float)x / (float)terrain_size_x;
            float uv_z = (float)z / (float)terrain_size_z;
            float height = GetHeightFromPixel((uint32_t)(hight_map_surface->w * uv_x), (uint32_t)(hight_map_surface->h * uv_z), hight_map_surface);
            heights[x][z] = height;
            vertices[GetVertexPosition(x, z)] = {
                glm::vec3(density * x, height, density * z),
                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                glm::vec2(uv_x, uv_z),
                ComputeNormal((uint32_t)(hight_map_surface->w * uv_x), (uint32_t)(hight_map_surface->h * uv_z), hight_map_surface),
                glm::vec3(1.0f, 1.0f, 1.0f)
            };
        }
    }
    SDL_FreeSurface(hight_map_surface);

    //Compute Indices
    std::vector<GLuint> indices;
    for (uint32_t x = 0; x < terrain_size_x - 1; x++)
    {
        for (uint32_t z = 0; z < terrain_size_z - 1; z++)
        {
            indices.push_back(GetVertexPosition(x, z));
            indices.push_back(GetVertexPosition(x + 1, z + 1));
            indices.push_back(GetVertexPosition(x + 1, z));

            indices.push_back(GetVertexPosition(x, z));
            indices.push_back(GetVertexPosition(x, z + 1));
            indices.push_back(GetVertexPosition(x + 1, z + 1));
        }
    }

    MeshData* mesh_data = entity->GetModule<MeshData>();
    if (mesh_data != NULL || mesh_data != nullptr)
    {
        mesh_data->SetMeshData(vertices, indices);
    } 

    Rigidbody* body = entity->GetModule<Rigidbody>();
    if (body != NULL || body != nullptr)
    {
        body->SetMass(0.0f);
        body->SetCollisionShape(new TerrainCollider(GetTerrainCollisionData()));
    }    
}

void Terrain::SetMaxHeight(float max_height)
{
    this->max_height = max_height;
}
void Terrain::SetTerrainSize(uint32_t x, uint32_t z)
{
    this->terrain_size_x = x;
    this->terrain_size_z = z;
}
void Terrain::SetDensity(float density)
{
    this->density = density;
}
void Terrain::SetHeightMapTexture(const char* hight_map)
{
    this->height_map = height_map;
}

float           Terrain::GetMaxHeight()
{
    return max_height;
}
void            Terrain::GetTerrainSize(uint32_t &x, uint32_t &z)
{
    x = terrain_size_x;
    z = terrain_size_z;
}
float           Terrain::GetDensity()
{
    return density;
}
const char*     Terrain::GetHeightMap()
{
    return height_map;
}

TerrainCollider::TerrainData    Terrain::GetTerrainCollisionData ()
{
    float x_size = terrain_size_x * density;
    float z_size = terrain_size_z * density;
    float* heights_data = new float[terrain_size_x * terrain_size_z];
    for (int i = 0; i < terrain_size_z; i++)
    {
        for (int j = 0; j < terrain_size_x; j++)
        {
            heights_data[(i * terrain_size_x) + j] = heights[j][i];
        }
    }

    return { x_size, z_size, heights_data, max_height };
}

SDL_Surface* Terrain::GetHeightMapImage()
{
    SDL_Surface* image_surface = IMG_Load((TEXTURE_PATH + height_map).c_str());
	if (!image_surface)
	{
		std::cout << "ERROR [IMG_Load]: " << height_map << " - " << IMG_GetError();
		return nullptr;
	}
	return image_surface;
}

glm::vec3   Terrain::ComputeNormal       (uint32_t x, uint32_t z, SDL_Surface* height_map_surface)
{
    float heightL = GetHeightFromPixel(x-1, z  , height_map_surface);
    float heightR = GetHeightFromPixel(x+1, z  , height_map_surface);
    float heightD = GetHeightFromPixel(x  , z-1, height_map_surface);
    float heightU = GetHeightFromPixel(x  , z+1, height_map_surface);

    glm::vec3 normal = glm::vec3(heightL - heightR, 0.5f, heightD - heightU);
    return glm::normalize(normal);
}

float       Terrain::GetHeightFromPixel  (uint32_t x, uint32_t z, SDL_Surface* height_map_surface)
{
    if (x < 0 || x > height_map_surface->w || z < 0 || z > height_map_surface->h)
        return 0;
    
    uint8_t r,g,b;
    SDL_GetRGB(GetPixelFromArray(x, z, height_map_surface), height_map_surface->format, &r, &g, &b);
    float height = r * g * b;
    height /= MAX_PIXEL_COLOR / 2.0f;
    height *= max_height;
    return height;
}
uint32_t    Terrain::GetPixelFromArray   (uint32_t x, uint32_t z, SDL_Surface* height_map_surface)
{
    uint8_t bpp = height_map_surface->format->BytesPerPixel;
    uint8_t* p = (uint8_t *)height_map_surface->pixels + z * height_map_surface->pitch + x * bpp;
    switch(bpp)
    {
        case 1:
            return *p;
        case 2:
            return *(uint16_t *)p;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(uint32_t *)p;
        default:
            std::cout << "WARNING: image formatting issues with hight map" << std::endl;
            return 0;
    }
}

uint32_t    Terrain::GetVertexPosition   (uint32_t x, uint32_t z)
{
    return x + (terrain_size_x * z);
}