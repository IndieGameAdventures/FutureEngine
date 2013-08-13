/*
 *	Copyright 2013 by Lucas Stufflebeam mailto:info@indiegameadventures.com
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *
 */

/*
*	Contains a a dynamic array that expands as needed.
*	Do not store pointers from the array as they may change if the array
*	needs to expand.
*/

#ifndef FUTURE_CORE_UTIL_ARRAY_H
#define FUTURE_CORE_UTIL_ARRAY_H

#include <future/core/type/type.h>
#include <future/core/object/threadsafeobject.h>
#include <future/core/memory/memory.h>



/*!
 *	\brief		A templated, dynamic, thread safe array
 *
 *	\details 	This templated array allows keeping track of a variable number of elements. There are a couple
 *				important things to take note of: First, don't store pointers or references to elemented within
 *				the array for more than immediate use. If the array needs to expand or shrink then the pointers
 *				will not longer point to valid data. Be careful adding or removing elements while iterating
 *				through the list. Be aware of other threads and if they might add or remove elements while
 *				the current thread is iterating through the array. Also note that the templated type must
 *				have a valid copy constructor and a valid equivalance operator (==)
 *			
 *				There are many functions, such as copying, deleting, moving and other things that may seem
 *				like this would be bad for storing an array of pointers to large objects, but it is actually
 *				perfectly fine. The object it's self isn't copied or moved but the pointer to the object is
 *				changed. You can store pointers to the objects the pointers in the array point to but do not
 *				store pointers to the pointers. Also be sure to free any memory these objects are using before
 *				clearing the array as they will not be automatically deleted, only the pointers to the objects
 *				will be gone.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		June 2013
 */
template<typename T>
class FutureArray : public FutureThreadSafeObject
{
public:
	FUTURE_DEFINE_MEMORY_OPERATORS(FutureArray);

	//! FutureArray Constructor. Creates a new, empty array.
	FutureArray();
	//! FutureArray Constructor. Creates an array with enough pre-allocated space to fit defaultSize elements.
	//! \param[in] defaultSize	The number of elements to make room for.
	FutureArray(u32 defaultSize);
	//! FutureArray copy constructor. This will copy the internal data of the provided array instead of instancing it.
	FutureArray(const FutureArray & a);
	//! FutureArray Destructor. This will delete the array and deconstruct the elements in the array
	~FutureArray();

	//! Retrieve the element at index i
	//! \param[in]	i	The index into the array of the desired element, must be less than Size() and greater than or equal to 0
	//! \return		A reference to the element, allowing for the element to be changed without re-adding it to the array
	T &	operator[](u32 i);

	//! Returns true if there are no elements in the array
	bool IsEmpty()
	{ return (m_size== 0); }

	//! Gets the current number of elements stored in the array
	u32	Size() const
	{ return m_size; }

	//! Gets a pointer to the internal array, be very careful manipulating this, it can break a lot of things
	T * a()
	{ return m_a; }

	//! Remove count number of elements starting at element i. (i + count) must be less than Size()
	//! \param[in]	i	The index into the array of the element to remove.
	//!	\param[in]	count	The number of elements to remove at i.
	// \return	The element at index i which was removed.
	T & Remove(u32 i, u32 count = 1);
	//! Performs a linear search for the provided element then removes it from the array.
	//! \param[in]	t	A reference to the element to remove. 
	//! \return	The element at index i which was removed.
	T & Remove(const T & t);

	//! Performs a linear search for the provided element.
	//! \param[in]	t	A reference to the element to find. 
	//! \return	The index of the element
	u32 IndexOf(const T & t);

	//! Expands the array until it is large enough to hold the specified number of elements. The array will most likely be larger than this.
	void EnsureSize(u32 count);
	
	//! Reduces any extra space being used so the internal size of the array is exactly the size needed for the current number of elements.
	void Shrink();

	//! Set the number of elements in the array.
	//! This does not actually change the internal size of the array but changes the number of elements
	//! stored in the array. If there are more than count elements in the array then the extra elements
	//! will be remove. If there are less than count elements then the new elements will be default
	//! initialized (NULL pointers if the array is storing pointers).
	void SetSize(u32 count);

	//! Removes all elements from the array and deletes the internal array.
	void Clear();

	//! Adds the element to the end of the array, expanding if needed
	void Add(const T & t);

	//! Adds all elements in the array to the end of this array, expanding as needed
	void AddMultiple(T * a, u32 count);
	
	//! Inserts the elements at the specified location, pushing all elements behind it back by one space.
	void Insert(u32 i, const T & t);

	//! This will attempt to find the element in the array, if is does not exist then the element will be added.
	void Ensure(const T & t);

	//! Adds the given element count times to the end of the array. Useful for initializing the array with default elements
	void Fill(const T & t, u32 count);

	//! Assignment operator. This will copy the internal data of the provided array instead of instancing it.
	void operator=(const FutureArray & a);

protected:

	//! Adds a new element to the array without locking the array
	void AddNoLock(const T & t);
	//! Ensures the internal size of the array without locking the array
	void EnsureSizeNoLock(u32 count);

	T * m_a;			//! The internal array
	u32	m_size;			//! The number of elements in the array
	u32	m_allocated;	//! The size of the internal array
};

#include <future/core/utils/container/array.inl>

#endif