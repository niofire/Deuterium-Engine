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
#include <vector>
#include "d_enum.h"

namespace deuterium
{




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
	dPtr<ShaderManager>		_shader_manager_ptr;
	dPtr<EventManager>		_event_manager_ptr;
};
	extern GlobalData g_data;
	
}