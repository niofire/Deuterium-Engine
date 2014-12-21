#pragma once
#include "d_Ptr.h"
#include "void_d_Ptr.h"
#include "d_typedef.h"
#ifdef DEUTERIUM_PC
#include "3rdParty/Glew/Include/glew.h"

#elif defined(EMSCRIPTEN)
#include <stdint.h>
#include <emscripten.h>
#include <SDL.h>
#include "SDL_opengl.h"
#elif defined(ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif	// _MCVS2012_
