#pragma once
#include "meta_asset.h"
#include "vertex_attribute_type.h"
namespace deuterium
{
	class ShaderComponentMetaNode
		: public MetaAsset
	{
	public:
		enum ShaderComponentType
		{
			VERTEX,
			FRAGMENT,
		};
	
		struct AttributeLocation
		{
		AttributeLocation(VertexAttributeType vertex_attrib_type, std::string attrib_name)
		{
			_vertex_attribute_type = vertex_attrib_type;
			_name = attrib_name;
		}
			VertexAttributeType _vertex_attribute_type;
			std::string _name;
	};

	public:
		ShaderComponentMetaNode(void);
		~ShaderComponentMetaNode(void);
	
		void load_meta(const MetaNode& node);

		//---------------------------------------------
		//			Accessor / Mutators
		//---------------------------------------------
		const std::string& name() { return _name;}
		const std::string& content() {return _content;}
		ShaderComponentType type() {return _type;}
		const std::vector<AttributeLocation>& attr_location() { _attr_locationDA;}

		//---------------------------------------------
		//			Member Variables
		//---------------------------------------------
	private:
		std::string _name;
		std::string _content;
		ShaderComponentType _type;
		std::vector<AttributeLocation> _attr_locationDA;
	};
}
