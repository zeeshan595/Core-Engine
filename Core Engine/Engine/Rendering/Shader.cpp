Shader::Shader(std::string vertex_shader_path, std::string fragment_shader_path)
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

    //Shader Attributes
    glBindAttribLocation(shader_program, 0, "vertex_position_model");
    glBindAttribLocation(shader_program, 1, "vertex_color");
    glBindAttribLocation(shader_program, 2, "vertex_uv");
    glBindAttribLocation(shader_program, 3, "vertex_normal_model");

    //Link Program
    glLinkProgram(shader_program);
    CheckForLinkErrors(shader_program);
    std::cout << "SUCCESS [Shader Loaded]" << std::endl;

    //Delete shaders
    glDeleteShader(vertex_shader_program);
    glDeleteShader(fragment_shader_program);
}

Shader::~Shader()
{
    glDeleteProgram(shader_program);
}

GLuint Shader::GetShaderProgram(){
    return shader_program;
}

GLuint Shader::LoadShaderFromMemory(const char * pMem, SHADER_TYPE shader_type)
{
    GLuint program = glCreateShader(shader_type);
    glShaderSource(program, 1, &pMem, NULL);
    glCompileShader(program);
    return program;
}

GLuint Shader::LoadShaderFromFile(const std::string& filename, SHADER_TYPE shader_type)
{
    std::string file_contents;
    std::ifstream file(filename, std::ios::in);
    if (!file.is_open())
    {
        std::cout << "File could not be loaded" << std::endl;
        return 0;
    }

    //calculate size
    if (file.good())
    {
        std::string line = "";
        while(!file.eof()) {
            std::getline(file, line);
            file_contents.append(line + "\n");
        }

        file.close();
        
        GLuint program = LoadShaderFromMemory(file_contents.c_str(), shader_type);
        return program;
    }
    return 0;
}

bool Shader::CheckForCompilerErrors(GLuint shader_program)
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

bool Shader::CheckForLinkErrors(GLuint program)
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