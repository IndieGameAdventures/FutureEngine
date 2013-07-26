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
*	Implementation of FutureArray
*/

template<typename T>
FutureArray<T>::FutureArray()
: m_a(NULL),
  m_size(0),
  m_allocated(0)
{
}

template<typename T>
FutureArray<T>::~FutureArray()
{	
	for(u32 i = 0; i < m_size; ++i)
	{
		m_a[i].~T();
	}

	if(m_a)
	{
		FUTURE_FREE(m_a);
	}
}
template<typename T>
FutureArray<T>::FutureArray(const FutureArray & a)
: m_a(NULL),
  m_size(0),
  m_allocated(0)
{
	AddMultiple(a.m_a, a.Size());
}
	
template<typename T>
void FutureArray<T>::operator=(const FutureArray & a)
{
	Clear();
	AddMultiple(a.m_a, a.Size());
}

template<typename T>
inline T & FutureArray<T>::operator[](u32 i)
{
	FUTURE_ASSERT((i >= 0) && (i < m_size));
	return m_a[i];
}

template<typename T>
T & FutureArray<T>::Remove(u32 i, u32 count)
{
	Lock();
	FUTURE_ASSERT((i >= 0) && (count > 0) && ((i + count) < m_size));
	
	T & element = m_a[i];
	for(u32 j = i + count; j < m_size; ++j)
	{
		m_a[j - count] = m_a[j];
	}

	for(u32 j = m_size - count; j < m_size; ++j)
	{
		m_a[j].~T();
	}

	m_size -= count;
	Unlock();
	return element;
}

template<typename T>
inline T & FutureArray<T>::Remove(const T & t)
{
	return Remove(IndexOf(t));
}

template<typename T>
inline u32 FutureArray<T>::IndexOf(const T & t)
{	
	Lock();
	for(u32 i = 0; i < m_size; ++i)
	{
		if(m_a[i] == t)
		{
			Unlock();
			return i;
		}
	}
	Unlock();
	return -1;
}

template<typename T>
void FutureArray< T >::EnsureSize(u32 size)
{
	Lock();
	EnsureSizeNoLock();
	Unlock();
}

template<typename T>
void FutureArray<T>::SetSize(u32 size)
{
	Lock();
	FUTURE_ASSERT(size >= 0);
	EnsureSizeNoLock(size);

	for(u32 i = size; i < m_size; ++i)
	{
		m_a[i].~T();
	}

	for(u32 i = m_size; i < size; ++i)
	{
		new (&m_a[i]) T;
	}

	m_size = size;
	Unlock();
}

template<typename T>
void FutureArray<T>::Clear()
{
	Lock();
	for(u32 i = 0; i < m_size; ++i)
	{
		m_a[i].~T();
	}

	if(m_a)
	{
		FUTURE_FREE(m_a);
	}

	m_allocated = 0;
	m_size = 0;
	m_a = NULL;
	Unlock();
}

template<typename T>
inline void FutureArray<T>::Add(const T & t)
{
	Lock();
	AddNoLock(t);
	Unlock();
}

template<typename T>
inline void FutureArray<T>::AddMultiple(T * a, u32 count)
{
	Lock();
	EnsureSizeNoLock(m_size + count);
	for(u32 i = 0; i < count; ++i)
	{
		AddNoLock(*a);
		++a;
	}
	Unlock();
}

template<typename T>
inline void FutureArray<T>::Ensure(const T & t)
{
	Lock();
	for(u32 i = 0; i < m_size; ++i)
	{
		if(m_a[i] == t)
		{
			Unlock();
			return;
		}
	}
	AddNoLock(t);
	Unlock();
}

template<typename T>
inline void FutureArray<T>::Fill(const T & t, u32 count)
{
	Lock();
	EnsureSizeNoLock(m_size + count);
	for(u32 i = 0; i < count; ++i)
	{
		AddNoLock(t);
	}
	Unlock();
}

template<typename T>
void FutureArray<T>::Insert(u32 i, const T & t)
{
	Lock();
	FUTURE_ASSERT((i >= 0) && (i <= m_size));
	EnsureSizeNoLock(m_size + 1);

	if(m_size == 0)
	{
		new (&m_a[m_size]) T(t);
	}
	else if(i == m_size)
	{
		AddNoLock(t);
		return;
	}
	else
	{
		new (&m_a[m_size]) T(m_a[m_size - 1]);
		for(u32 j = m_size - 1; j > i; --j)
		{
			m_a[j] = m_a[j - 1];
		}

		m_a[i] = t;
	}

	++m_size;
	Unlock();
}


template<typename T>
inline void FutureArray<T>::AddNoLock(const T & t)
{
	EnsureSizeNoLock(m_size + 1);
	m_a[m_size++] = t;
}

template<typename T>
void FutureArray< T >::EnsureSizeNoLock(u32 size)
{
	FUTURE_ASSERT(size >= 0);

	if(size <= m_allocated)
	{
		return;
	}

	if(m_allocated <= 0)
	{
		m_allocated = 4;
	}
	// double the size until it is greater than 1024, 
	// at that point add 256 until it is as big as needed
	while(m_allocated < size)
	{
		if(m_allocated >= 1024)
		{ 
			m_allocated += 256;
		}
		else
		{
			m_allocated *= 2;
		}
	}

	u32 bytes = m_allocated * sizeof(T);
	T * aNew = static_cast<T *>(FUTURE_ALLOC(bytes, L"FutureArray"));
	FUTURE_ASSERT(aNew);

	for(u32 i = 0; i < m_size; ++i)
	{
		new (&aNew[i]) T(m_a[i]);
		m_a[i].~T();
	}

	if(m_a)
	{
		FUTURE_FREE(m_a);
	}

	m_a = aNew;
}