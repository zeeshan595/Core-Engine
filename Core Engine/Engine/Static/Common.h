#ifndef _COMMON
#define _COMMON

//GENERAL
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include <list>
#include <map>

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

//GLOBAL VARIABLES
std::map<int, bool> keys_pressed;
glm::vec2 mouse_delta;
glm::vec2 mouse_position;
float delta_time;
int WIDTH;
int HEIGHT;

#endif