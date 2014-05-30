#pragma once
#include "shader_technique.h"

namespace deuterium
{
class ShaderTechniqueCache
{
public:
	~ShaderTechniqueCache(void);
	static ShaderTechniqueCache& access_cache();
	void			add_technique(ShaderTechnique technique);

	ShaderTechnique* get_technique_by_name(const char* technique_name);
	ShaderTechnique* get_technique_by_id(const U32 id);
	U32				 get_technique_id_by_name(const char* name);
private:
	ShaderTechniqueCache(void);
	static ShaderTechniqueCache s_shader_technique_cache;
	std::vector<ShaderTechnique> _cache;
};
}
