#pragma once
#include "render_target.h"
#include "shader_pass.h"
#include "string_helper.h"
namespace deuterium
{

template <typename T>
class Assets	{
public:
	struct AssetData
	{
		std::string _name;
		dPtr<T> _asset_ptr;
	};
	Assets() 
		{ 
			AssetData t;
			t._name = "null";
			t._asset_ptr = dPtr<T>();
			_asset_data_DA.push_back(t);
		}

		void add_asset(U32& id, dPtr<T> asset_ptr, std::string asset_name)
		{
			AssetData data;
			data._name = asset_name;
			data._asset_ptr = asset_ptr;

			this->_asset_data_DA.push_back(data);
		}

		dPtr<T> get_asset(std::string asset_name)
		{
			for(int i = 0; i < _asset_data_DA.size(); ++i)
			{
				if(StringHelper::is_identical_string(_asset_data_DA[i]._name,asset_name))
				{
					return _asset_data_DA[i]._asset_ptr;
				}
			}
			return dPtr<T>();
		}

		const U32& get_asset_id(const std::string& name)
		{
			for(int i = 0 ; i  < _asset_data_DA.size(); ++i)
			{
				if(StringHelper::is_identical_string(_asset_data_DA[i]._name,name))
					return i;
			}
			return 0;
		}
		
		const std::string& get_asset_name(const U32& id)
		{
			if(id < _asset_data_DA.size())
			{
				return _asset_data_DA[i]._name;
			}
			return "null";
		}

		dPtr<T> get_asset(U32 id)
		{
			if(id < _asset_data_DA.size())
			{
				return _asset_data_DA[i]._asset_ptr;
			}
			return dPtr<T>();
		}
		bool exists(const char* name)
		{
			dPtr<T> ptr = this->get_asset(name);
			return !ptr.is_null();
		}
	private:
		std::vector<AssetData> _asset_data_DA;
	};
}