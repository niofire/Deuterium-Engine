#include "mesh.h"
#include "math.h"

#include <stack>
#include <iostream>
#include <fstream>
#include <string>

namespace deuterium
{

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

void Swap(U16& x, U16& y)
{
	U16 temp  = x;
	x = y;
	y = x;
}

void Mesh::load_mesh(const char* i_sFilePath)
{
	//Indice vectors
	std::vector<U16>	l_PositionIndices;
	std::vector<U16>	l_TexCoordIndices;
	std::vector<U16>	l_NormalIndices;

	bool l_bHasTexCoord		= false;
	bool l_bHasPosition		= false;
	bool l_bHasNormals		= false;

	//Vertex vectors
	std::vector<Vec3f>	l_Positions;
	std::vector<Vec2f>	l_TexCoords;
	std::vector<Vec3f>	l_Normals;

	std::ifstream fileIn(i_sFilePath);
	
	
	//Check if filed open properly
	if(!fileIn.is_open())
	{
		std::cerr << "Cannot open " << i_sFilePath << std::endl;
		return;
		exit(1);
	}

	
	
	//line will hold each line of the .obj file consecutively
	std::string line = "";

	//Parse the whole file...
	while (std::getline(fileIn,line))
	{
		//Position
		if(line.substr(0,2) == "v ")
		{
			l_bHasPosition = true;
			std::istringstream s(line.substr(2));
			Vec3f v; s >> v.x; s >> v.y; s >> v.z;
			l_Positions.push_back(v);

		}
		//Load texture coordinates
		else if(line.substr(0,2) == "vt")
		{
			l_bHasTexCoord = true;
			//Parse the coordinates, then store into temp vector
			std::istringstream s(line.substr(3));
			Vec2f v;
			s >> v.x; s >> v.y;
			l_TexCoords.push_back(v);
		}
		else if(line.substr(0,2) == "vn")
		{
			l_bHasNormals = true;
			//Parse the coordinates, then store into temp vector
			std::istringstream s(line.substr(3));
			Vec3f v;
			s >> v.x; s >> v.y; s >> v.z;
			l_Normals.push_back(v);
		}


		// Load in indices, 2 sets of 3 per line 
		// (1 for position, 1 for texture coordinates)
		// of form =>  f 297/1 97/1 295/1
		else if( line.substr(0,2) == "f ")
		{
			// position/Texcoord/Normals
			//Parse indice position and store in temp vector

			std::istringstream s(line.substr(2));
			line = line.substr(2);

			std::vector<U16> l_IndexList;
			l_IndexList.reserve(9);
			U16 index = 0;
			//fill two index arrays
			//first check position, else fill vt, else fill only normals
			//First, vertex index
			size_t pos = 0;

			//Load in all indices

			while((pos = line.find("/")) != std::string::npos)
			{
				//get number before "/"
				s.str(line.substr(0,pos));
				s >> index;
				l_IndexList.push_back(--index);

				//Get number after "/"
				line = line.substr(pos + 1);
				s.clear();
				s.str(line);
				s >> index;
				l_IndexList.push_back(--index);
				s.clear();
				//set string after the last number taken
				line = line.substr((line.find(" ") == std::string::npos ? 0: line.find(" ")));
			}

			//Store indices into a stack
			std::stack<U16> l_Stack;
			for(int i = l_IndexList.size() - 1; i >= 0; --i)
				l_Stack.push(l_IndexList[i]);

			while(!l_Stack.empty())
			{
				if(l_bHasPosition)
				{
					l_PositionIndices.push_back(l_Stack.top());
					l_Stack.pop();
				}
				if(l_bHasTexCoord)
				{
					l_TexCoordIndices.push_back(l_Stack.top());
					l_Stack.pop();
				}
				if(l_bHasNormals)
				{
					l_NormalIndices.push_back(l_Stack.top());
					l_Stack.pop();
				}					
			}

		}


		else if( line[0] == '#') {/* comment */}
		else { /* ignore line */ }
	}

	fileIn.close();
	//Get the position of indices
	U32 l_NumberOfIndices = 0;
	U32 l_NumberOfElements = 0;

	if(l_bHasTexCoord)
	{
		l_NumberOfIndices = l_PositionIndices.size();
		l_NumberOfElements = l_Positions.size();
	}
	else if(l_bHasNormals)
	{
		l_NumberOfIndices = l_NormalIndices.size();
		l_NumberOfElements = l_Normals.size();
	}
	else if( l_bHasTexCoord)
	{
		l_NumberOfIndices = l_TexCoordIndices.size();
		l_NumberOfElements = l_TexCoords.size();
	}

	//resize any missing element's indice array
	if(!l_bHasTexCoord)
		l_PositionIndices.resize(l_NumberOfIndices,0);
	if(!l_bHasNormals)
		l_NormalIndices.resize(l_NumberOfIndices,0);
	if(!l_bHasTexCoord)
		l_TexCoordIndices.resize(l_NumberOfIndices,0);

	U16* l_IndexDataPtr = NULL;
	U8* l_VertexDataPtr = NULL;


	_index_buffer_container.reset();
	_vertex_buffer_container.reset();

	//Add Streams to vertexbuffer
	U32 l_StreamElements = 0;
	if(l_bHasPosition)
		l_StreamElements |= POSITION0;
	if(l_bHasNormals)
		l_StreamElements |= NORMAL;
	if(l_bHasTexCoord)
		l_StreamElements |= TEXCOORD0;

	S32 l_MeshStreamNumber = _vertex_buffer_container.add_stream(l_StreamElements);
	//Lock index and vertex buffers in order to store data into them
	_index_buffer_container.lock_buffer((void**)&l_IndexDataPtr,0,l_NumberOfIndices * sizeof(U16));

	//Prepare the output Data vector

	//hashmap data structure
	struct IndiceData
	{
		U16 FinalIndice;
		U16 PositionIndice;
		U16 NormalIndice;
		U16 TexCoordIndice;
	};

	//Hashmap containing the indices
	std::vector<std::vector<IndiceData> > l_HashMap;

	//default indice data stored in the hashmap
	std::vector<IndiceData> l_Default;
	l_HashMap.resize(l_NumberOfIndices,l_Default);

	//Vertices in order of storage
	std::vector<IndiceData> l_VerticesToStore;

	//Used to count 
	U16	l_IndexCounter = 0;

	//cycle through all indices
	for(U32 i = 0; i < l_NumberOfIndices; ++i)
	{
		//Get hash key
		U32 l_HashKey = (l_PositionIndices[i] * 13 + l_NormalIndices[i] * 17 + l_TexCoordIndices[i] * 19) % l_NumberOfIndices;

		//If this is not the first element with this specific HashKey
		U32 l_HashMapSize = l_HashMap[l_HashKey].size();

		//True if the element is already a HashMap entry
		bool ElementHasBeenFound = false;

		//Cycle through the hashmap bucket located at the hashmap key.
		for(U32 HashElementIndex = 0; HashElementIndex < l_HashMapSize; ++HashElementIndex)
		{
			//If entry is already existing, store it into the IndexBuffer
			if(l_HashMap[l_HashKey][HashElementIndex].PositionIndice == l_PositionIndices[i]
			&&	l_HashMap[l_HashKey][HashElementIndex].NormalIndice == l_NormalIndices[i]
			&&	l_HashMap[l_HashKey][HashElementIndex].TexCoordIndice == l_TexCoordIndices[i])
			{
				l_IndexDataPtr[i] = l_HashMap[l_HashKey][HashElementIndex].FinalIndice;
				ElementHasBeenFound = true;
			}
		}

		//If entry does not exist, create a new entry
		if(!ElementHasBeenFound)
		{
			//Create new HashMap entry
			IndiceData Data;
			Data.FinalIndice		= l_IndexCounter;
			Data.PositionIndice		= l_PositionIndices[i];
			Data.NormalIndice		= l_NormalIndices[i];
			Data.TexCoordIndice		= l_TexCoordIndices[i];

			//Add new Hashmap Entry in HashMap
			l_HashMap[l_HashKey].push_back(Data);

			//Store data in IndexBufferObject datastream
			l_IndexDataPtr[i] = l_IndexCounter;

			//store the Indice data in the VerticeToStore vector, which will be transferred in the VBO afterwards
			l_VerticesToStore.push_back(Data);

			l_IndexCounter++;
		}
	}
	_index_buffer_container.unlock_buffer();

	
	//Get stream data
	StreamData& l_sData = _vertex_buffer_container.GetStreamData(l_MeshStreamNumber);
	//Lock vertex buffer
	_vertex_buffer_container.lock_buffer((void**)&l_VertexDataPtr,l_MeshStreamNumber,0,l_VerticesToStore.size() * l_sData.GetStreamStride());


	U32 l_Offset = 0;
	U32 l_Stride = l_sData.GetStreamStride();

	//Go through the VerticesToStore vector and load all the data from the vector into the VBO
	for(U32 i = 0; i < l_VerticesToStore.size();++i)
	{
		//Check if positions are present and load at appropriate offset
		if(l_sData.ContainsStreamComponents(POSITION0))
		{
			l_Offset = l_sData.GetStreamComponentOffset(POSITION0);
			memcpy(((char*)l_VertexDataPtr + l_Offset + l_Stride * i),
				l_Positions[l_VerticesToStore[i].PositionIndice].GetPtr(),
				l_sData.GetStreamTypeByteSize(POSITION0));
		}

		if(l_sData.ContainsStreamComponents(NORMAL))
		{
			//Get the offset of the element in the vertex buffer object
			l_Offset = l_sData.GetStreamComponentOffset(NORMAL);
			
			//Copy value from the temp vector to the VBO
			memcpy(
				((char*)l_VertexDataPtr +l_Offset + l_Stride * i),
				l_Normals[l_VerticesToStore[i].NormalIndice].GetPtr(),
				l_sData.GetStreamTypeByteSize(NORMAL));

		}
		//Check of TexCoord0 are present and load at appropriate offset
		if(l_sData.ContainsStreamComponents(TEXCOORD0))
		{
			l_Offset = l_sData.GetStreamComponentOffset(TEXCOORD0);
			memcpy(((char*)l_VertexDataPtr +l_Offset + l_Stride * i),
				l_TexCoords[l_VerticesToStore[i].TexCoordIndice].GetPtr(),
				l_sData.GetStreamTypeByteSize(TEXCOORD0));
		}
	}
	_vertex_buffer_container.unlock_buffer();

}
}