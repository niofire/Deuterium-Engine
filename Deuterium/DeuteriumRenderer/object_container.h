#pragma once
#include "global_data.h"
#include <stack>
#include <vector>

//------------------------------------------------------------------
//					ObjectContainer class
//	The object container is optimized as an ADT which hold pointers to objects.
//	It diverges from the standard vector class through its faster "remove" operations
//	and its lack of linear ordering.
//	Index 0 is reserved as a NULL index.
namespace deuterium
{

template <class T>
class ObjectContainer
{
public:
	//--------------------------------------------------------------
	//					constructor / destructor
	//--------------------------------------------------------------
	ObjectContainer();
	virtual ~ObjectContainer();


	//--------------------------------------------------------------
	//					core functions
	//--------------------------------------------------------------
	U32							add(T object);
	bool						remove_at(U32 object_id);
	T*							get_at(U32 id);
	bool						replace_at(U32 i_ID,T object);
	bool						validate_id(U32 object_id);
	inline U32					size(){ return _object_list.size(); };
private:

	//--------------------------------------------------------------
	//					helper function
	//--------------------------------------------------------------

private:

	std::vector<T>			_object_list;
	std::vector<bool>		_object_usage_map;
	std::stack<U32>			_unused_id_stack;
	
};



template <class T>
ObjectContainer<T>::ObjectContainer()
{
}

template <class T>
ObjectContainer<T>::~ObjectContainer()
{

}

template <class T>
U32 ObjectContainer<T>::add(T object)
{
	if(_unused_id_stack.empty())
	{
		//Register a new object into the Object Usage Mapping
		_object_usage_map.push_back(true);
		
		//Insert object at end of vector and return id
		
		_object_list.push_back(object);
		return _object_list.size();
	}
	else
	{
		//Get unused ID from the unused ID stack
		U32 index = _unused_id_stack.top();
		_unused_id_stack.pop();

		//Register the object at the given location in the Object Usage Mapping
		_object_usage_map[index] = true;

		//Insert object into vector, return the id
		_object_list[index] = object;
		return index + 1;
	}
}

template <class T>
bool ObjectContainer<T>::remove_at(U32 object_id)
{


	
	//check if Id is valid
	if(!validate_id(object_id))
		return false;

	//Change the object mapping and return indice to the unusged indice stack
	_object_usage_map[object_id] = false;

	//push object into stack
	_unused_id_stack.push(object_id);
	
	return true;
}

template <class T>
bool ObjectContainer<T>::validate_id(U32 object_id)
{
	object_id--;
	//Checks if id is larger than the objectlist size
	if(object_id > _object_list.size())
		return false;

	//Check if object has been removed
	if(!_object_usage_map[object_id])
		return false;

	return true;
}

template <class T>
bool ObjectContainer<T>::replace_at(U32 object_id, T object)
{
	
	if(!validate_id(object_id))
		return false;
	_object_list[object_id] = object;
}

template <class T>
T*	ObjectContainer<T>::get_at(U32 object_id)
{
	if(!validate_id(object_id))
	{
		//TODO -> Debug call: Object does not exists
		return NULL;
	}
	return &_object_list[object_id - 1];
}

}