#include "meta_asset.h"
#include "d_ptr.h"

namespace deuterium
{
	MetaAsset::MetaAsset(void)
	{
	}


	MetaAsset::~MetaAsset(void)
	{

	}

	void MetaAsset::refresh_instances()
	{
		for(U32 i = 0; i < _asset_instancesDA.size();++i)
		{
			if(!_asset_instancesDA[i].is_null())
			{
				IAsset& asset = _asset_instancesDA[i].value();
			
				//reload the meta into the asset in order to update its content
				//asset.load_meta(dPtr<AssetMeta>(this));

				//recompile with the same asset id
				asset.compile(asset.runtime_id());
			}

		}
	}

	void MetaAsset::add_instance(dPtr<IAsset> aPtr)
	{
		//check for null ptr
		if(aPtr.is_null())
			return;

		//TODO check for duplicates

		_asset_instancesDA.push_back(aPtr);
	}
}