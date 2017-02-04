#ifndef _COMMON
#define _COMMON

#ifdef __MINGW32__
#include <windows.h>
#endif

//GENERAL
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include <list>
#include <map>
#include <stdio.h>

//OPEN AL
#include <AL/al.h>
#include <AL/alc.h>

//OPEN GL
#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_Image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>

//MATHS
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtx/string_cast.hpp>
#include <GLM/gtc/constants.hpp>

//PATHS
const std::string ASSET_PATH    = "assets/";
const std::string SHADER_PATH   = ASSET_PATH + "shaders/";
const std::string TEXTURE_PATH  = ASSET_PATH + "textures/";
const std::string FONT_PATH     = ASSET_PATH + "fonts/";
const std::string MODEL_PATH    = ASSET_PATH + "models/";
const std::string SOUND_PATH    = ASSET_PATH + "sound/";

//Static
#include "Screen.h"
#include "Time.h"
#include "Input.h"
#include "Transform.h"
#include "Vertex.h"
#include "OBJLoader.h"
#include "Cube.h"
#include "Plane.h"
#include "Fog.h"
//Base classes
#include "../Modules/Module.h"
#include "../Core/Entity.h"
//Audio
#include "../Audio/Audio.h"
#include "../Audio/AudioClip.h"
//Rendering
#include "../Rendering/Camera.h"
#include "../Rendering/Light.h"
#include "../Rendering/Texture.h"
#include "../Rendering/CubeTexture.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Surface.h"
#include "../Rendering/Skybox.h"
#include "../Rendering/UI.h"
//Environment
#include "../Core/Environment.h"
//Physics
#include "../Physics/Raycast.h"
//Modules
#include "../Modules/Mesh.h"
#include "../Modules/Terrain.h"
#include "../Modules/AudioSource.h"


#endif