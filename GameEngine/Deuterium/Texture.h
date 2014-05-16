#pragma once
#include "global_data.h"
#include "3rdParty/LodePNG/LodePNG.h"

namespace deuterium
{
class Texture
{
public:
	//--------------------------------------------------------------------
	//					Constructor / Destructor
	//--------------------------------------------------------------------
	Texture();
	virtual ~Texture();

	bool				LoadDDSTexture(char* file_path);
	bool				LoadPngTexture(char* file_path);

	inline	GLuint		texture_handle()	{ return _texture_handle;};
private:
	GLuint				_texture_handle;



};
}