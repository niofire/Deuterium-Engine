#pragma once
#include <string>
#include <fstream>

#include "string_helper.h"
#include "3rdParty\rapidjson\stringbuffer.h"
#include "3rdParty\rapidjson\document.h"
#include "3rdParty\rapidjson\writer.h"
#include "3rdParty\rapidjson\error\en.h"
#include "meta_data_value.h"


namespace deuterium
{
	
class MetaNode
{
public:
	MetaNode(void);
	~MetaNode(void);

	static std::string get_json_from_file(const char* filename);

	//----------------------------------------------
	//			Instantiation functions
	//----------------------------------------------
	bool load(const rapidjson::Value& json_value,const std::string& name);	


	//-----------------------------------------------
	//			Node Operations
	//-----------------------------------------------

	//true if node has no values whatsoever
	bool						is_null();
	
	//if DNE, returns a null node
	const MetaNode&				fetch_child(const std::string& name);
	
	//check if node has a child with given name
	bool						is_child(const std::string& name);

private:
	void						process_value(const rapidjson::Value& v, const std::string& name);

	//-----------------------------------------------
	//			Accessor / Mutator 
	//-----------------------------------------------
	const std::string&			name() {return _name;}
	
	//returns empty string for undetermined value
	const MetaDataValue&		fetch_value(const std::string& name);
	
	//returns whether this value exists in this node
	bool						has_value(const std::string& name);
	
	//------------------------------------------
	//			Operator Overload
	//------------------------------------------
	inline bool operator==(const MetaNode& rhs) const {return _name.compare(rhs._name) == 0 && _nodeDA.empty() && _meta_valueDA.empty(); }
	inline bool operator!=(const MetaNode& rhs) const { return !(*this == rhs);}
public:
	static const MetaNode null_value;
private:
	//Name of the node
	std::string _name;

	//contains all pairs
	std::vector<MetaDataValue> _meta_valueDA;
	
	//contains all child nodes
	std::vector<MetaNode> _nodeDA;
};
}
