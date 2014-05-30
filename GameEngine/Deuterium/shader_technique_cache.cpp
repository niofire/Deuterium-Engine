#include "shader_technique_cache.h"
#include "string_helper.h"

namespace deuterium
{

	
ShaderTechniqueCache::ShaderTechniqueCache(void)
{
}


ShaderTechniqueCache::~ShaderTechniqueCache(void)
{
}

ShaderTechniqueCache& ShaderTechniqueCache::access_cache()
{
	return ShaderTechniqueCache::s_shader_technique_cache;
}


ShaderTechnique* ShaderTechniqueCache::get_technique_by_name(const char* technique_name)
{
	for(U32 i = 0; i < _cache.size(); ++i)
	{
		if(StringHelper::is_identical_string( _cache[i].name() , technique_name))
		{
			return &_cache[i];
		}
	}
	return NULL;
}

ShaderTechnique* ShaderTechniqueCache::get_technique_by_id(const U32 id)
{
	if(id < _cache.size())
		return &_cache[id];
	return NULL;
}

U32				 ShaderTechniqueCache::get_technique_id_by_name(const char* name)
{
	for(U32 i = 0; i < _cache.size(); ++i)
	{
		if(StringHelper::is_identical_string( _cache[i].name() , name))
		{
			return i;
		}
	}
	return -1;
}

}