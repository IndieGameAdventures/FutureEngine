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

/*class FutureString
{
public:
	
	// returns the character at the given index
	static char		CharAt(const char * string, u32 i);
	// checks to see if this string is currently empty
	static bool		IsEmpty(const char * string);
	// returns the length of the string
	static u32		Length(const char * string);
	// clears the sting
	static void		Clear(char * string);

	// changes all chars to upper or lower case
	// If createNew is true then this will return a new string and
	// not change this one, otherwise this string will be changed
	static void		ToUppercase(const char * string, char * out, u32 maxSize);
	static void		ToLowercase(const char * string, char * out, u32 maxSize);

	// compares with the given string
	// returns -1 if this string comes before the other alphabetically
	// returns 0 if the two string are equal
	// returns 1 if this string comes after the other alphabetically
	static u32		Compare(const char * str0, const char * str1);
	// returns true if this string ends with, starts with, or contains the given string
	static bool		EndsWith(const char * string, const char * ending);
	static bool		StartsWith(const char * string, const char * start);
	static bool		Contains(const char * string, const char * contains);

	// returns the index of the given string or -1 if it doesn't exist
	static s32		IndexOf(const char * string, char contains);
	static s32		LastIndexOf(const char * string, char contains);
	static s32		IndexOf(const char * string, const char * contains);
	static s32		LastIndexOf(const char * string, const char * contains);

	// finds all occurrences of the given string and returns a new string using replace in those locations
	static void		Replace(const char * string, const char * find, const char * replace, char * out, u32 maxSize);

	// splits the string around the given string and places the sections in ary
	static void		Split(const char * string, const char * find, FutureArray<const char *> * ary);
	
	// Returns the requested substring of this string, if count is < 0 this will go to the end of the string
	static void		SubString(const char * string, u32 start, u32 count, char * out, u32 maxSize);

	// Returns a new string the is equal to this + str
	static void		Concat(const char * str0, const char * str1, char * out, u32 maxSize);
};*/

#endif