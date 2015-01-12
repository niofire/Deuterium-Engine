#pragma once
#include <vector>
#include "d_typedef.h"
#include "IAsset.h"

namespace deuterium
{
	class AssetLibrary
	{
	public:
		~AssetLibrary(void);
		//-------------------------------------------
		//			Query functions
		//-------------------------------------------
		dPtr<IAsset>		fetch_asset(const U32& runtime_id);
		bool				is_valid(const U32& id);


		//-------------------------------------------
		//			Instantiation functions	
		//-------------------------------------------
	private:
		void				load_library();


		//-------------------------------------------
		//			Singleton functions
		//-------------------------------------------
	public:
		static AssetLibrary	instance();

	private:
		AssetLibrary(void);
		static dPtr<AssetLibrary> s_asset_library;

	private:

		std::vector< dPtr< AssetMeta> > _asset_metaPtrDA;
		std::vector<dPtr <IAsset> > _assetPtrDA;
	}; 
}



