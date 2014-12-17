#pragma once
#include "d_typedef.h"

class IAsset
{
public:

	//Load the asset 
	virtual void load(const char* content) = 0;

	//compile the asset, binding it to the current rendering context
	virtual void compile(U32 id) = 0;

	const U32& asset_id() { return _asset_id;}

protected:
	U32 _asset_id;

};