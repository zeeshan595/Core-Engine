
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
    if (model.positions.size() == model.texCoords.size() && model.texCoords.size() == model.normals.size())
    {
        const int VERTS_LEN = model.positions.size();
        const int INDICES_LEN = model.indices.size();
        vertices.resize(VERTS_LEN);
        indices.resize(INDICES_LEN);

        for (int i = 0; i < VERTS_LEN; i++)
        {
            vertices[i] = {
                model.positions[i],
                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                model.texCoords[i],
                model.normals[i],
                glm::vec3(0.0f, 0.0f, 0.0f)
                };
        }

        for (int i = 0; i < INDICES_LEN; i++)
        {
            indices[i] = model.indices[i];
        }
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