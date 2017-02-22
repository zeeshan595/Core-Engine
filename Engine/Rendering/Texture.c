Texture::Texture(int width, int height, bool is_depth)
{
	//Delete the old loaded texture if it is still there.
	if (texture_map != 0)
		glDeleteTextures(1, &texture_map);

	//Generate a new texture
	glGenTextures(1, &texture_map);
	glBindTexture(GL_TEXTURE_2D, texture_map);
	if (!is_depth)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	//Set Texture Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

Texture::Texture(const std::string& filename)
{
	//Delete the old loaded texture if it is still there.
	if (texture_map != 0)
		glDeleteTextures(1, &texture_map);
	
	//Use SDL surface to load texture from a file.
	SDL_Surface* image_surface = IMG_Load((TEXTURE_PATH + filename).c_str());
    if (!image_surface)
    {
        std::cout << "ERROR [IMG_Load]: " << filename << " - " << IMG_GetError();
        return;
    }

    texture_map = ConvertSDLSurfaceToTexture(image_surface);
    SDL_FreeSurface(image_surface);

	ApplyTextureFilter();
}

void Texture::ApplyTextureFilter()
{
	glBindTexture(GL_TEXTURE_2D, texture_map);

	if (Quality::texture_filter == TextureFilterType::NONE)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else if (Quality::texture_filter == TextureFilterType::MIP_MAP)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		if (Quality::mip_map_amount > 1.0f)
			Quality::mip_map_amount = 1.0f;
		else if (Quality::mip_map_amount < 0.0f)
			Quality::mip_map_amount = 0.0f;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -Quality::mip_map_amount);
	}
	else if (Quality::texture_filter == TextureFilterType::ANISOTROPIC)
	{
		if (!glewIsSupported("GL_EXT_texture_filter_anisotropic"))
		{
			std::cout << "WARNING: Anistropic filtering not supported" << std::endl;
			return;
		}

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);
		GLfloat max_anistropic;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anistropic);

		if (Quality::anistropic_filter_amount > max_anistropic)
			Quality::anistropic_filter_amount = max_anistropic;
		else if (Quality::anistropic_filter_amount < 0)
			Quality::anistropic_filter_amount = 0;

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Quality::anistropic_filter_amount);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture_map);
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