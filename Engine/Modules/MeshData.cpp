
void MeshData::Start()
{
    ComputeTangents();
    
    //Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //Create VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    //Create EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    Vertex::AttributeInfo();
}

void MeshData::Stop()
{
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void MeshData::SetMeshData(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
{
    this->vertices = vertices;
    this->indices = indices;
}

void MeshData::LoadOBJ(const char* filename)
{
    IndexedModel model = OBJModel(MODEL_PATH + filename).ToIndexedModel();
    // ObjLoader::ObjStructure model = ObjLoader::LoadObj(filename);
    vertices.resize(model.positions.size());
    indices.resize(model.indices.size());
    for (uint32_t i = 0; i < vertices.size(); i++)
    {
        vertices[i] = {
            model.positions[i],
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            model.texCoords[i],
            model.normals[i],
            glm::vec3(1.0f, 1.0f, 1.0f)
        };
    }
    for (uint32_t i = 0; i < indices.size(); i++)
    {
        indices[i] = model.indices[i];
    }
}

std::vector<uint32_t>       MeshData::GetIndices()
{
    return indices;
}

GLuint                      MeshData::GetVAO()
{
    return VAO;
}

void MeshData::ComputeTangents()
{
    for (int i = 0; i < vertices.size() / 3; i++)
    {
        glm::vec3 delta_position1 = vertices[(i*3) + 1].position - vertices[(i*3) + 0].position;
        glm::vec3 delta_position2 = vertices[(i*3) + 2].position - vertices[(i*3) + 0].position;
        glm::vec2 delta_uv1 = vertices[(i*3) + 1].uv - vertices[(i*3) + 0].uv;
        glm::vec2 delta_uv2 = vertices[(i*3) + 2].uv - vertices[(i*3) + 0].uv;

        float r = 1.0f / (delta_uv1.x * delta_uv2.y - delta_uv1.y * delta_uv2.x);
        delta_position1 *= delta_uv2.y;
        delta_position2 *= delta_uv1.y;
        glm::vec3 tangent = delta_position1 - delta_position2;
        vertices[(i*3) + 0].tangent = tangent;
        vertices[(i*3) + 1].tangent = tangent;
        vertices[(i*3) + 2].tangent = tangent;
    }
}

std::string MeshData::GetBaseDir(const std::string &filepath)
{
  if (filepath.find_last_of("/\\") != std::string::npos)
    return filepath.substr(0, filepath.find_last_of("/\\"));
  return "";
}