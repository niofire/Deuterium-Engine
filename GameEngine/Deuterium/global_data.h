#pragma once
#include "d_Ptr.h"
#include "deuterium_error_stack.h"
#include "void_d_Ptr.h"
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
#include "d_enum.h"
#include "render_pass.h"
#define ADD_RENDER_PASS_TYPE(enum_name,int_value,str_value) const dEnum RenderPass::RenderPassType::enum_name = dEnum(int_value,#str_value);
#define AAA(X,Y) _pass_value_name_DA.push_back(RenderPass::Pair(X,Y));
namespace deuterium
{
	ADD_RENDER_PASS_TYPE(MESH,0,"mesh");
	ADD_RENDER_PASS_TYPE(POST_PROCESS,1,"post_process");



	class GameCore;
	class Renderer;
	class MeshManager;
	class ShaderManager;
	class PrimitiveTypeHelper;
	class EventManager;

	
	


	



	
//------------------------------------------------------------------------
//					GlobalData class
//------------------------------------------------------------------------

struct GlobalData
{
public:	
	dPtr<GameCore>			_game_core_ptr;
	dPtr<MeshManager>		_mesh_manager_ptr;
	dPtr<Renderer>			_renderer_ptr;
	dPtr<ShaderManager>	_shader_manager_ptr;
	dPtr<EventManager>		_event_manager_ptr;
};
	extern GlobalData g_data;
	
}