#pragma once
#include "d_ptr.h"
#include "deuterium_error_stack.h"
#include "void_d_ptr.h"
#ifdef DEUTERIUM_PC
#include "3rdParty/Glew/Include/glew.h"
typedef unsigned	__int32	U32;
typedef				__int32	S32;
typedef unsigned	__int16	U16;
typedef				__int16 S16;
typedef unsigned	__int8	U8;
typedef				__int8	S8;
#pragma comment(lib, "SDL2/lib/SDL2main.lib")
#pragma comment(lib, "SDL2/lib/SDL2.lib")
#pragma comment(lib, "Glew/lib/glew32.lib")
#pragma comment(lib, "opengl32.lib")
#elif defined(EMSCRIPTEN)
#include <stdint.h>
#include <emscripten.h>
#include <SDL.h>
#include "SDL_opengl.h"
typedef uint32_t  	U32;
typedef int32_t 	S32;
typedef	uint16_t 	U16;
typedef int16_t 	S16;
typedef	uint8_t		U8;
typedef int8_t		S8;
#elif defined(ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <inttypes.h>
typedef uint32_t  	U32;
typedef int32_t 	S32;
typedef	uint16_t 	U16;
typedef int16_t 	S16;
typedef	uint8_t		U8;
typedef int8_t		S8;
#endif	// _MCVS2012_
#include <vector>
namespace deuterium
{
	class GameCore;
	class Renderer;
	class MeshManager;
	class ShaderManager;
	class PrimitiveTypeHelper;
	class EventManager;

	
	
	enum StreamType
	{
		POSITION0	= 1,
		POSITION1	= 2,
		COLOR		= 4,
		NORMAL		= 8,
		TANGENT		= 16,
		TEXCOORD0	= 32,
		TEXCOORD1	= 64,
		TEXCOORD2	= 128,
		TEXCOORD3	= 256,
		TEXCOORD4	= 512,
		TEXCOORD5	= 1024,
		TEXCOORD6	= 2048,
		TEXCOORD7	= 4096,
		NULL0		= 8192,
	};





	
//------------------------------------------------------------------------
//					GlobalData class
//------------------------------------------------------------------------

struct GlobalData
{
public:	
	GameCore*				_game_core_ptr;
	MeshManager*			_mesh_manager_ptr;
	Renderer*				_renderer_ptr;
	ShaderManager*			_shader_manager_ptr;
	EventManager*			_event_manager_ptr;
};
	extern GlobalData g_data;
}