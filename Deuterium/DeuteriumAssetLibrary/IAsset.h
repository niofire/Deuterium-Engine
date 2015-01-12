#pragma once
#include "d_typedef.h"
#include "d_ptr.h"
#include "meta_node.h"
namespace deuterium
{
	class AssetMeta;

	class IAsset
	{
	public:

		//compile the asset, binding it to the current rendering context
		virtual void compile(U32 id) { _runtime_id = id;}

		const U32& runtime_id() { return _runtime_id;}

		void load_meta(dPtr<MetaNode> node) { _metaPtr = node;}

	protected:
		U32 _runtime_id;
		dPtr<MetaNode> _metaPtr;

	};
}