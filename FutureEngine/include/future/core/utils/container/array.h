/*!
*	Copyright 2013 by Lucas Stufflebeam mailto:info@indiegameadventures.com
*
*	Thank you for taking a look at my code. If you like it, please click
*	the donation button at the bottom of the sidebar on my blog. Thanks!
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

template<typename T>
class FutureArray : public FutureThreadSafeObject
{
public:
	FutureArray();
	~FutureArray();

	// Retrieve element at index i
	T &	operator[](u32 i);

	// Returns true if there are no elements in the array
	bool IsEmpty()
	{ return (m_size== 0); }

	// Gets the current length of the array
	u32	Size() const
	{ return m_size; }

	// Gets a pointer to the internal array
	// Be very careful manipulating this, it can break a lot of things
	T * a()
	{ return m_a; }

	// Remove the specified element
	T & Remove(u32 i, u32 count = 1);
	T & Remove(const T & t);

	// Return the index of the object
	u32 IndexOf(const T & t);

	// Expands the array until it is large enough to hold the specified number
	// of elements. The array will most likely be larger than this.
	void EnsureSize(u32 count);
	
	// Set the number of elements in the array.
	void SetSize(u32 count);

	// Removes all elements from the array.
	void Clear();

	// Adds the element to the end of the array
	void Add(const T & t);

	// Adds all elements in the array to the end of this array
	void AddMultiple(T * a, u32 count);
	
	// Inserts the elements at the specified location
	void Insert(u32 i, const T& t);

	// This will search for an element in the array and add the element if it is does not already exist
	void Ensure(const T & t);

	// Adds the given element p_c times to the end of the array
	void Fill(const T & t, u32 count);

protected:

	// Arrays do not support direct assignment.
	FutureArray(const FutureArray & a);
	void operator=( const FutureArray & a);
	
	void AddNoLock(const T & t);
	void EnsureSizeNoLock(u32 count);

	T * m_a;
	u32	m_size;
	u32	m_allocated;
};

#include <future/core/utils/container/array.inl>

#endif