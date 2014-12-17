#include "Texture.h"
#include <fstream>
#include <vector>
#include <iostream>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
namespace deuterium
{
Texture::Texture()
{
	this->_texture_handle = 0;
}

Texture::~Texture()
{
	//glDeleteTextures(1,&_texture_handle);
}

bool Texture::LoadPngTexture(char* i_FilePath)
{
  std::vector<unsigned char> image; //the raw pixels
  unsigned int width, height;

  //decode
  unsigned int error = lodepng::decode(image, width, height, i_FilePath);

  //if there's an error, display it
  if(error)
	  std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  // Create one OpenGL texture
  if(_texture_handle == 0)
		glGenTextures(1, &_texture_handle);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, _texture_handle);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	
	//If not all mipmap were created
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* load the mipmaps */ 
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,&image[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,0);
	return true;

}



bool Texture::LoadDDSTexture(char* i_FilePath)
{
	unsigned char header[124];

	FILE *fp; 
	
	/* try to open the file */ 
	fp = fopen(i_FilePath, "rb"); 
	if (fp == NULL)
	{
		std::cerr << "File did not open: " << i_FilePath;
		return 0; 
	}
   
	/* verify the type of file */ 
	char filecode[4]; 
	fread(filecode, 1, 4, fp); 
	if (strncmp(filecode, "DDS ", 4) != 0) { 
		fclose(fp); 
		return 0; 
	}
	
	/* get the surface desc */ 
	fread(&header, 124, 1, fp); 

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width	     = *(unsigned int*)&(header[12]);
	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);

 
	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */ 
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char)); 
	fread(buffer, 1, bufsize, fp); 
	/* close the file pointer */ 
	fclose(fp);

	unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4; 
	unsigned int format;
	switch(fourCC) 
	{ 
	case FOURCC_DXT1: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
		break; 
	default: 
		free(buffer); 
		return 0; 
	}

	// Create one OpenGL texture
	if(_texture_handle == 0)
		glGenTextures(1, &_texture_handle);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, _texture_handle);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	
	//If not all mipmap were created
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
	unsigned int offset = 0;

	/* load the mipmaps */ 
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) 
	{ 
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,  
			0, size, buffer + offset);
		int x = glGetError();
		offset += size; 
		width  /= 2; 
		height /= 2; 
	} 

	free(buffer); 
	glBindTexture(GL_TEXTURE_2D,0);
	return true;
}



}