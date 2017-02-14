void Particle::GenerateBuffers()
{
    if (particles_amount > 0)
    {
        Particle::vertices = Plane::vertices;
        Particle::indices  = Plane::indices;

        //Create VAO
        glGenVertexArrays(1, &Particle::VAO);
        glBindVertexArray(Particle::VAO);
        //Create VBO
        glGenBuffers(1, &Particle::VBO);
        glBindBuffer(GL_ARRAY_BUFFER, Particle::VBO);
        glBufferData(GL_ARRAY_BUFFER, Particle::vertices.size() * sizeof(Vertex), &Particle::vertices[0], GL_STATIC_DRAW);
        //Create EBO
        glGenBuffers(1, &Particle::EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Particle::EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Particle::indices.size() * sizeof(GLuint), &Particle::indices[0], GL_STATIC_DRAW);
        
        //Shader Info
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texture));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    }
}

Particle::Particle()
{
    particles_amount++;
    GenerateBuffers();
}

Particle::~Particle()
{
    particles_amount--;
    if (particles_amount == 0)
    {
        glDeleteBuffers(1, &Particle::EBO);
        glDeleteBuffers(1, &Particle::VBO);
        glDeleteVertexArrays(1, &Particle::VAO);
    }
}