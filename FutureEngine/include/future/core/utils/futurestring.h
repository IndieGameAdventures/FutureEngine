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
*	A string wrapper with many helpful functions.
*	Note that all functions requiring a string will accept
*	wchar_t * or char * but wchar_t * is preferred to reduce
*	conversion costs.
*
*	While this wrapper class is partially mutable, the internal string is not
*	and must be reconstructed anytime the string is changed therefore
*	FutureString should always be const to help reduce string copies
*/

#ifndef FUTURE_CORE_UTIL_STRING_H
#define FUTURE_CORE_UTIL_STRING_H

#include <future/core/type/type.h>
#include <future/core/object/threadsafeobject.h>
#include <future/core/utils/container/array.h>

class FutureString : public FutureThreadSafeObject
{
public:

	FutureString();
	FutureString(const FutureString & p_str);
	FutureString(const char * p_a);
	FutureString(const string p_chz);
	~FutureString();
	
	// returns the character at the given index
	wchar_t	CharAt(u32 i) const;
	// checks to see if this string is currently empty
	bool	IsEmpty() const;
	// returns the length of the string
	u32		Length() const;
	// clears the sting
	void	Clear();

	// changes all chars to upper or lower case
	// If createNew is true then this will return a new string and
	// not change this one, otherwise this string will be changed
	FutureString &	ToUppercase(bool createNew = false);
	FutureString &	ToLowercase(bool createNew = false);
	FutureString	ToUppercase() const;
	FutureString	ToLowercase() const;

	// compares with the given string
	// returns -1 if this string comes before the other alphabetically
	// returns 0 if the two string are equal
	// returns 1 if this string comes after the other alphabetically
	u32			Compare(const FutureString & str) const;
	// returns true if this string ends with, starts with, or contains the given string
	bool		EndsWith(const FutureString & str) const;
	bool		StartsWith(const FutureString & str) const;
	bool		Contains(const FutureString & str) const;

	// returns the index of the given string or -1 if it doesn't exist
	s32			IndexOf(const FutureString & str) const;
	s32			LastIndexOf(const FutureString & str) const;

	// finds all occurrences of the given string and returns a new string using replace in those locations
	FutureString	Replace(const FutureString & find, const FutureString & replace) const;

	// splits the string around the given string and places the sections in ary
	void			Split(const FutureString & str, FutureArray<FutureString> * ary) const;
	
	// Returns the requested substring of this string, if count is < 0 this will go to the end of the string
	FutureString	SubString(u32 start, u32 count = -1) const;

	// Returns a new string the is equal to this + str
	FutureString	Concat(const FutureString & str) const;

	// returns the actual array of chars in this string
	// be very careful using this because a buffer size has already been
	// created and going over that buffer size with cause memory corruption
	// if you change the size of the string, be sure to call vUpdateSize otherwise
	// this string's length will not be correct
	wchar_t *	Writable();
	void		UpdateSize();

	string			WideString() const;
	const char *	CharString() const;

	// standard operators
	FutureString &	operator=(const wchar_t * str);
	FutureString &	operator=(const char * str);
	FutureString &	operator=(const FutureString & p_str);
	FutureString &	operator+=(const wchar_t * str);
	FutureString &	operator+=(const char * str);
	FutureString &	operator+=(const FutureString & str);

	FutureString	operator+(const wchar_t * str) const;
	FutureString	operator+(const char * str) const;
	FutureString	operator+(const FutureString & str) const;

	operator bool() const
	{ return !IsEmpty(); }

	bool operator!() const
	{ return IsEmpty(); }

	operator string() const
	{ return WideString(); }

	operator const char *() const
	{ return CharString(); }

	wchar_t operator[](u32 i) const
	{ return CharAt(i); }


	static wchar_t * WideFromChar(const char * str);
	static char * CharFromWide(string str);

protected:

	void		ForceSize(u32 size);

	wchar_t *	m_string;
	u32			m_length;

};

#endif