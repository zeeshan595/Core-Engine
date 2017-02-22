#ifndef _QUALITY
#define _QUALITY

enum TextureFilterType
{
    NONE = 0,
    MIP_MAP = 1,
    ANISOTROPIC = 2
};

class Quality
{
public:
    static TextureFilterType texture_filter;
    static float anistropic_filter_amount;
    static float mip_map_amount;

    static GLfloat GetMaxAnistropicAmount(){
        GLfloat max_anistropic;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anistropic);
        return max_anistropic;
    }

    static void EnableMultisampling(){
        glEnable(GL_MULTISAMPLE);
    }
    static void DisableMultisampling(){
        glDisable(GL_MULTISAMPLE);
    }
};
TextureFilterType   Quality::texture_filter             = TextureFilterType::ANISOTROPIC;
float               Quality::anistropic_filter_amount   = 2;
float               Quality::mip_map_amount             = 0.4f;

#endif