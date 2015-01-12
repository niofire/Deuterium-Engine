#include "meta_node.h"
#include "d_typedef.h"
namespace deuterium
{
	const MetaNode MetaNode::null_value;

	MetaNode::MetaNode(void)
	{
		_name = "";
	}


	MetaNode::~MetaNode(void)
	{
		
	}


	bool MetaNode::load(const rapidjson::Value& json_value, const std::string& name)
	{
		using namespace rapidjson;

		if(json_value.IsArray())
		{
			//parse through array
			for(U32 i = 0; i < json_value.Size(); ++i)
			{
				const Value& v = json_value[i];
				
				process_value(v,_name);
			}
		}
		else
		{
			//Parse through object
			for (Value::ConstMemberIterator itr = json_value.MemberBegin(); itr != json_value.MemberEnd(); ++itr)
			{
				//Get name
				std::string name;
				if(itr->name.IsString())
					name = itr->name.GetString();
				
				//process value..
				const Value& v = itr->value;
				process_value(itr->value,name);
			}
		}
		return true;
	}

	bool MetaNode::is_null()
	{
		return *this == MetaNode::null_value;
	}

	void MetaNode::process_value(const rapidjson::Value& v, const std::string& name)
	{
		using namespace rapidjson;
		//Check if value is a node
		if(v.IsArray() || v.IsObject())
		{
			MetaNode node;
			node.load(v,name);
			_nodeDA.push_back(node);
		}
		else {
			MetaDataValue value;
			value.set_value(v);
			value.set_name(name);
			_meta_valueDA.push_back(value);
		}
	}

	const MetaNode& MetaNode::fetch_child(const std::string& name)
	{
		for(U32 i = 0; i < _nodeDA.size();++i)
		{
			MetaNode& node = _nodeDA[i];
			if(node.name().compare(name) == 0)
				return node;
		}
		return MetaNode::null_value;
	}

	const MetaDataValue& MetaNode::fetch_value(const std::string& name)
	{
		for(U32 i = 0; i < _meta_valueDA.size(); ++i)
		{
			MetaDataValue &m = _meta_valueDA[i];
			if(name.compare(m.name()) == 0)
				return m;
		}

		return MetaDataValue::null_value;
	}

	bool MetaNode::has_value(const std::string& name)
	{
		return fetch_value(name).is_null();
	}

}