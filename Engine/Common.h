#ifndef _COMMON
#define _COMMON

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc

#ifdef __MINGW32__
#include <windows.h>
#endif

//GENERAL
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include <list>
#include <map>
#include <stdio.h>
#include <ctime>

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
#include <glm/gtx/quaternion.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtx/string_cast.hpp>
#include <GLM/gtc/constants.hpp>

//Bullet Physics Library
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <LinearMath/btIDebugDraw.h>

//PATHS
const std::string ASSET_PATH    = "Assets/";
const std::string SHADER_PATH   = ASSET_PATH + "Shaders/";
const std::string TEXTURE_PATH  = ASSET_PATH + "Textures/";
const std::string FONT_PATH     = ASSET_PATH + "Fonts/";
const std::string MODEL_PATH    = ASSET_PATH + "Models/";
const std::string SOUND_PATH    = ASSET_PATH + "Sound/";
bool  ENVIRONMENT_CHANGED       = false;

//Static
#include "Static/Time.h"
#include "Static/Vertex.h"
#include "Static/Input.h"
#include "Static/Screen.h"
#include "Static/OBJLoader.h"
#include "Static/Fog.h"
#include "Static/Cube.h"
#include "Static/Plane.h"

//Structure
#include "Structure/Transform.h"
#include "Structure/Module.h"
#include "Structure/Entity.h"

//Graphics
#include "Graphics/Texture.h"
#include "Graphics/CubeTexture.h"
#include "Graphics/Shader.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"
#include "Graphics/Light.h"
#include "Graphics/Skybox.h"

//Audio
#include "Audio/Audio.h"
#include "Audio/AudioClip.h"

//Physics
#include "Physics/GLDebugDrawer.h"
#include "Physics/Physics.h"
#include "Physics/Collider.h"
#include "Physics/BoxCollider.h"
#include "Physics/BallCollider.h"
#include "Physics/TerrainCollider.h"

//Game Engine
#include "Core/Environment.h"
#include "Core/Graphics.h"
#include "Core/Core.h"

//Modules
#include "Modules/MeshData.h"
#include "Modules/MeshRenderer.h"
#include "Modules/Rigidbody.h"
#include "Modules/AudioSource.h"
#include "Modules/AudioListener.h"
#include "Modules/Terrain.h"
#include "Modules/UI.h"

#endif