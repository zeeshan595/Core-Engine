CubeTexture::CubeTexture(const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ)
{
    glGenTextures(1, &cube_texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cube_texture);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    LoadCubeMapFace(posX, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
    LoadCubeMapFace(negX, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
    LoadCubeMapFace(posY, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
    LoadCubeMapFace(negY, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
    LoadCubeMapFace(posZ, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
    LoadCubeMapFace(negZ, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
}

CubeTexture::~CubeTexture()
{
    glDeleteTextures(1, &cube_texture);
}

GLuint CubeTexture::GetTextureMap()
{
    return cube_texture;
}

void CubeTexture::LoadCubeMapFace(const std::string& filename, GLenum face)
{
    SDL_Surface	*imageSurface = IMG_Load((TEXTURE_PATH + filename).c_str());
    if (!imageSurface){

        std::cout << "Can't Load	image " << filename << " " << IMG_GetError();
        return;
    }

    GLint nOfColors = imageSurface->format->BytesPerPixel;

    GLenum	textureFormat = GL_RGB;
    GLenum	internalFormat = GL_RGB8;

    if (nOfColors == 4)					//	contains	an	alpha	channel
    {
        if (imageSurface->format->Rmask == 0x000000ff){
            textureFormat = GL_RGBA;
            internalFormat = GL_RGBA8;
        }
        else
        {
            textureFormat = GL_BGRA;
            internalFormat = GL_RGBA8;
        }
    }
    else if (nOfColors == 3)					//	no	alpha	channel
    {
        if (imageSurface->format->Rmask == 0x000000ff){
            textureFormat = GL_RGB;
            internalFormat = GL_RGB8;
        }
        else
        {
            textureFormat = GL_BGR;
            internalFormat = GL_RGB8;
        }
    }
    else
    {
        std::cout << "ERROR [SDL_Surface -> Texture]: Image is not True Color" << std::endl;
        return;
    }
    glTexImage2D(face, 0, internalFormat, imageSurface->w, imageSurface->h, 0, textureFormat, GL_UNSIGNED_BYTE, imageSurface->pixels);

    SDL_FreeSurface(imageSurface);
}