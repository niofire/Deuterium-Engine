#pragma once
#include <vector>
#include "d_ptr.h"
#include "d_typedef.h"
#include "rendering_asset.h"
namespace deuterium
{
	class Material;
	class RenderingAssetLibrary
	{
	public:


	public:

		~RenderingAssetLibrary();



		dPtr<RenderingAsset>	fetch_asset(U32 rendering_asset_type, const U32& id);
		void					create_asset(U32 rendering_asset_type, const std::string& content);

		//----------------------------------------
		//			Singleton functions
		//----------------------------------------
	public:
		static RenderingAssetLibrary& instance();
		
	private:
		RenderingAssetLibrary();
		static dPtr<RenderingAssetLibrary> s_assetLibrary;

	private:
		std::vector<std::vector<dPtr<RenderingAsset> > > _rendering_assetDA;

	};
}