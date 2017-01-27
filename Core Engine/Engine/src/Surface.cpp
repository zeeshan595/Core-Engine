Surface::Surface(std::string vertex_shader_path, std::string fragment_shader_path)
{
    //Get Shaders
    GLuint vertex_shader_program = 0;
    vertex_shader_program = LoadShaderFromFile(SHADER_PATH + vertex_shader_path, VERTEX_SHADER);
    CheckForCompilerErrors(vertex_shader_program);

    GLuint fragment_shader_program = 0;
    fragment_shader_program = LoadShaderFromFile(SHADER_PATH + fragment_shader_path, FRAGMENT_SHADER);
    CheckForCompilerErrors(fragment_shader_program);

    //Attach Shader Programs
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader_program);
    glAttachShader(shader_program, fragment_shader_program);
    glLinkProgram(shader_program);
    CheckForLinkErrors(shader_program);
    std::cout << "SUCCESS [Shader Loaded]" << std::endl;

    glDeleteShader(vertex_shader_program);
    glDeleteShader(fragment_shader_program);

    //Shader Attributes
    glBindAttribLocation(shader_program, 0, "vertexPosition");
    //glBindAttribLocation(shader_program, 1, "vertexTexCoords");
    //glBindAttribLocation(shader_program, 2, "vertexNormal");
}

Surface::~Surface()
{
    glDeleteProgram(shader_program);
}

void Surface::ApplyTexture(std::string filename)
{
    texture = std::shared_ptr<Texture>(new Texture(TEXTURE_PATH + filename));

    glBindTexture(GL_TEXTURE_2D, texture->GetTextureMap());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);
}

GLuint Surface::LoadShaderFromMemory(const char * pMem, SHADER_TYPE shader_type)
{
    GLuint program = glCreateShader(shader_type);
    glShaderSource(program, 1, &pMem, NULL);
    glCompileShader(program);
    return program;
}

GLuint Surface::LoadShaderFromFile(const std::string& filename, SHADER_TYPE shader_type)
{
    std::string file_contents;
    std::ifstream file;
    file.open(filename.c_str(), std::ios::in);
    if (!file)
    {
        std::cout << "File could not be loaded" << std::endl;
        return 0;
    }

    //calculate size
    if (file.good())
    {
        file.seekg(0, std::ios::end);
        unsigned long len = file.tellg();
        file.seekg(std::ios::beg);
        if (len == 0)
        {
            std::cout << "File has no contents" << std::endl;
            return 0;
        }
        file_contents.resize(len);
        file.read(&file_contents[0], len);
        file.close();
        GLuint program = LoadShaderFromMemory(file_contents.c_str(), shader_type);
        return program;
    }
    return 0;
}

bool Surface::CheckForCompilerErrors(GLuint shader_program)
{
    GLint isCompiled = 0;
    glGetShaderiv(shader_program, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader_program, GL_INFO_LOG_LENGTH, &maxLength);

        std::string infoLog;
        infoLog.resize(maxLength);
        glGetShaderInfoLog(shader_program, maxLength, &maxLength, &infoLog[0]);

        std::cout << "Shader not compiled" << infoLog << std::endl;

        glDeleteShader(shader_program);
        return true;
    }
    return false;
}

bool Surface::CheckForLinkErrors(GLuint program)
{
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        std::string infoLog;
        infoLog.resize(maxLength);
        
        glGetShaderInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        std::cout << "Shader not linked" << infoLog << std::endl;

        glDeleteProgram(program);
        return true;
    }

    return false;
}