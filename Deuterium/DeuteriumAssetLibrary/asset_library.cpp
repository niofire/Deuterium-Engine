#include "asset_library.h"
#include "config_path.h"
namespace deuterium
{
	//Path variables


	AssetLibrary::AssetLibrary()
	{
		load_library();
	}


	AssetLibrary::~AssetLibrary(void)
	{
	}

	dPtr<IAsset> AssetLibrary::fetch_asset(const U32& id)
	{
		if(!is_valid(id))
			return dPtr<IAsset>();

		return _assetPtrDA[id];
	}

	bool AssetLibrary::is_valid(const U32& id)
	{
		//check for out of bound id
		if(id >= _assetPtrDA.size())
			return false;
		return true;
	}

	//-----------------------------
	//		Singleton Functions
	//-----------------------------
	dPtr<AssetLibrary> AssetLibrary::s_asset_library;

	AssetLibrary AssetLibrary::instance()
	{
		if(s_asset_library.is_null())
			s_asset_library.alloc(new AssetLibrary());
		
		return s_asset_library.value();
	}

	void AssetLibrary::load_library()
	{
		const std::string map_filepath = ASSET_RESOURCE_MAP_PATH;



	}


}