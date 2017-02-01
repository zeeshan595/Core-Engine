void Terrain::CreateTerrain(int size_x, int size_y, float density)
{
    terrain_size_x = size_x;
    terrain_size_y = size_y;
    std::shared_ptr<Mesh> attached_mesh = attached_to->GetModule<Mesh>();
    if (attached_mesh == nullptr){
        attached_mesh = attached_to->AddModule<Mesh>();
        std::shared_ptr<Shader> myShader = std::shared_ptr<Shader>(new Shader("defaultVS.glsl", "defaultFS.glsl"));
        std::shared_ptr<Surface> mySurface = std::shared_ptr<Surface>(new Surface(myShader));
        mySurface->ApplyTexture(std::shared_ptr<Texture>(new Texture("texture.png")));
        attached_mesh->ApplySurface(mySurface);
    }
    
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    vertices.resize((terrain_size_x + 1) * (terrain_size_y + 1));

    for (int x = 0; x < terrain_size_x + 1; x++){
        for (int y = 0; y < terrain_size_y + 1; y++){
            vertices[GetVertexPosition(x, y)] = {
                glm::vec3(density * x, 0.0f, density * y),
                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                glm::vec2(x, y),
                glm::vec3(0.0f, 1.0f, 0.0f)
            };
        }
    }

    for (int x = 0; x < terrain_size_x; x++){
        for (int y = 0; y < terrain_size_y; y++){
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
