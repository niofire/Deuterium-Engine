#pragma once
namespace deuterium
{
	/*
		The gBuffer class contains statistical data regarding the VRAM used by the gBuffer render targets.
		Moreover, all operations used on the gBuffer passes by this class.
	*/
class gBuffer
{
public:
	gBuffer(void);
	~gBuffer(void);

	//Initialize the render targets and the shaders used to populate the gBuffer.
	//A valid gl context is required
	bool init();

	 
private:


};
}
