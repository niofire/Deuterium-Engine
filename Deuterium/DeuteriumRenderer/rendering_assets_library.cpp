#include "rendering_assets_library.h"

namespace deuterium
{

	RenderingAssetLibrary::RenderingAssetLibrary()
	{
		//Initializes the RenderingAsset dynamic arrays so all rendering asset types can be cached.
		for (int i = 0; i < RenderingAsset::NUM_TYPES; ++i)
		{
			_rendering_assetDA.push_back(std::vector<dPtr<RenderingAsset>>());
		}

	}

	RenderingAssetLibrary::~RenderingAssetLibrary()
	{

	}

	RenderingAssetLibrary& RenderingAssetLibrary::instance()
	{
		if (s_assetLibrary.is_null())
			s_assetLibrary.alloc(new RenderingAssetLibrary());

		return s_assetLibrary.value();
	}

	dPtr<RenderingAsset> RenderingAssetLibrary::fetch_asset(U32 rendering_asset_type, const U32& id)
	{
		dPtr<RenderingAsset> asset_ptr;
		//Check if rendering asset type is valid..
		if (rendering_asset_type >= RenderingAsset::NUM_TYPES)
			return asset_ptr;

		std::vector<dPtr<RenderingAsset>>& assetDA = _rendering_assetDA[rendering_asset_type];
		//Check if ID is valid..
		if (id >= assetDA.size())
			return asset_ptr;

		//Check if null ptr fills location
		if (assetDA[id].is_null())
			return asset_ptr;
		
		//return valid rendering asset
		asset_ptr = assetDA[id];
		return asset_ptr;
	}

	void	RenderingAssetLibrary::create_asset(U32 rendering_asset_type, const std::string& content)
	{
		if (rendering_asset_type >= RenderingAsset::NUM_TYPES)
			return;
		switch (rendering_asset_type)
		{
		case RenderingAsset::MATERIAL:
			break;
		case RenderingAsset::MESH:
			break;
		default:
			break;
		}
	}

}