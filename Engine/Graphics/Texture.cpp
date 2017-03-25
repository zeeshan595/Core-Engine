Texture::Texture(const char* filename)
{
    SDL_Surface* image_surface = IMG_Load((TEXTURE_PATH + filename).c_str());
    if (!image_surface)
    {
        std::cout << "ERROR [IMG_Load]: " << filename << " - " << IMG_GetError();
        return;
    }
    texture_map = ConvertSDLSurfaceToTexture(image_surface);
    SDL_FreeSurface(image_surface);
    ApplyImageFilter();
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture_map);
}

void Texture::ApplyImageFilter()
{
    glBindTexture(GL_TEXTURE_2D, texture_map);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
}

GLuint Texture::ConvertSDLSurfaceToTexture(SDL_Surface* surface)
{
    GLuint textureID = 0;
	GLint nOfColors = surface->format->BytesPerPixel;

	GLenum	textureFormat = GL_RGB;
	GLenum	internalFormat = GL_RGB8;

	if (nOfColors == 4)					//	contains	an	alpha	channel
	{
		if (surface->format->Rmask == 0x000000ff){
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
		if (surface->format->Rmask == 0x000000ff){
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
		return 0;
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, surface->w, surface->h, 0, textureFormat, GL_UNSIGNED_BYTE, surface->pixels);

	return textureID;
}

SDL_Surface* Texture::LoadImageFromFile(const char* filename)
{
	//Use SDL surface to load texture from a file.
	SDL_Surface* image_surface = IMG_Load((TEXTURE_PATH + filename).c_str());
	if (!image_surface)
	{
		std::cout << "ERROR [IMG_Load]: " << filename << " - " << IMG_GetError();
		return nullptr;
	}
	return image_surface;
}

const GLuint Texture::GetTextureMap()
{
    return texture_map;
}