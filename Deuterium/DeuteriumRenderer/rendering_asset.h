#pragma once
class RenderingAsset
{
public:
	enum 
	{
		MESH = 0,
		MATERIAL,

	};
	static const int NUM_TYPES = 2;


	RenderingAsset();
	~RenderingAsset();
};

