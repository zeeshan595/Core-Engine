#ifndef _VERTEX
#define _VERTEX

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texture;
    glm::vec3 normal;
    glm::vec3 tangent;
};

std::vector<Vertex> ComputeVertexTangents(std::vector<Vertex> vert)
{
    std::vector<Vertex> vertices = vert;
    for (int i = 0; i < vertices.size() / 3; i++)
    {
        glm::vec3 delta_position1 = vertices[(i*3) + 1].position - vertices[(i*3) + 0].position;
        glm::vec3 delta_position2 = vertices[(i*3) + 2].position - vertices[(i*3) + 0].position;
        glm::vec2 delta_uv1 = vertices[(i*3) + 1].texture - vertices[(i*3) + 0].texture;
        glm::vec2 delta_uv2 = vertices[(i*3) + 2].texture - vertices[(i*3) + 0].texture;

        float r = 1.0f / (delta_uv1.x * delta_uv2.y - delta_uv1.y * delta_uv2.x);
        delta_position1 *= delta_uv2.y;
        delta_position2 *= delta_uv1.y;
        glm::vec3 tangent = delta_position1 - delta_position2;
        vertices[(i*3) + 0].tangent = tangent;
        vertices[(i*3) + 1].tangent = tangent;
        vertices[(i*3) + 2].tangent = tangent;
    }

    return vertices;
}

#endif