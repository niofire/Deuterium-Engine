#pragma once
#include "IAsset.h"
#include <vector>
#include "dll_exporter.h"
#include "meta_node.h"
namespace deuterium
{
class DALAPI MetaAsset
{
public:
	MetaAsset(void);
	virtual ~MetaAsset(void);

	//pass in the meta content..
	virtual void load_meta(const MetaNode& node) = 0;

	//refresh all instances created from this meta with the updated content
	void refresh_instances();

	const U32& storage_id() { return _storage_id;}

protected:
	void add_instance(dPtr<IAsset> asset);

private:
	U32 _storage_id;
	std::vector<dPtr<IAsset>> _asset_instancesDA;
};
}

