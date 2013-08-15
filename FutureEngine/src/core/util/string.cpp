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
*	Implementation of FutureString
*
*/
#include <future/core/utils/futurestring.h>
#include <string.h>
#include <stdlib.h>

/*
wchar_t FutureString::CharAt(u32 i) const
{
	return *(m_string + i);
}

bool FutureString::IsEmpty() const
{
	return (m_length == 0);
}

u32 FutureString::Length() const
{
	return m_length;
}

void FutureString::Clear()
{
	FUTURE_SAFE_DELETE(m_string);
	m_string = NULL;
	m_length = 0;
}

FutureString& FutureString::ToUppercase(bool createNew)
{
	if(createNew)
	{
		FutureString str = m_string;
		return str.ToUppercase();
	}
	else
	{
		wchar_t * wideString = m_string;
		while(*wideString)
		{
			*wideString = (wchar_t)toupper(*wideString);
			++wideString;
		}
		return *this;
	}
}

FutureString& FutureString::ToLowercase(bool createNew)
{
	if(createNew)
	{
		FutureString str = m_string;
		return str.ToLowercase();
	}
	else
	{
		wchar_t * wideString = m_string;
		while(*wideString)
		{
			*wideString = (wchar_t)tolower(*wideString);
			++wideString;
		}
		return *this;
	}
}
FutureString FutureString::ToUppercase() const
{
	FutureString str = m_string;
	return str.ToUppercase();
}

FutureString FutureString::ToLowercase() const
{
	FutureString str = m_string;
	return str.ToLowercase();
}

u32 FutureString::Compare(const FutureString & str) const
{
	return wcscmp(WideString(), str.WideString());
}

bool FutureString::EndsWith(const FutureString & str) const
{
	s32 i = Length() - 1;
	s32 j = str.Length() - 1;
	for(; i >= 0 && j >= 0; --i, --j)
	{
		if(CharAt((u32)i) != str.CharAt((u32)j))
		{
			return false;
		}
	}

	return j < 0;
}

bool FutureString::StartsWith(const FutureString & str) const
{
	u32 i = 0;
	u32 j = 0;
	for(; i < Length() && j < str.Length(); ++i, ++j)
	{
		if(CharAt(i) != str.CharAt(j))
		{
			return false;
		}
	}
	return j >= str.Length() - 1;
}

bool FutureString::Contains(const FutureString & str) const
{
	for(u32 i = 0; i < Length() - str.Length(); ++i)
	{
		if(CharAt(i) == str.CharAt(0))
		{
			u32 k = 1;
			for(u32 j = i + 1; j < Length() && k < str.Length(); ++j, ++k)
			{
				if(CharAt(j) != str.CharAt(k))
				{
					break;
				}
			}
			if(k == str.Length())
			{
				return true;
			}
		}
	}
	return false;
}

s32	 FutureString::IndexOf(const FutureString & str) const
{
	for(u32 i = 0; i < Length() - str.Length(); ++i)
	{
		if(CharAt(i) == str.CharAt(0))
		{
			u32 k = 1;
			for(u32 j = i + 1; j < Length() && k < str.Length(); ++j, ++k)
			{
				if(CharAt(j) != str.CharAt(k))
				{
					break;
				}
			}
			if(k == str.Length())
			{
				return (s32)i;
			}
		}
	}
	return -1;
}

s32 FutureString::LastIndexOf(const FutureString & str) const
{
	for(s32 i = Length() - str.Length(); i >= 0; --i)
	{
		if(CharAt((u32)i) == str.CharAt(0))
		{
			u32 k = 1;
			for(s32 j = i + 1; j < Length() && k < str.Length(); ++j, ++k)
			{
				if(CharAt((u32)j) != str.CharAt(k))
				{
					break;
				}
			}
			if(k == str.Length())
			{
				return i;
			}
		}
	}
	return -1;
}


FutureString FutureString::Replace(const FutureString & find, const FutureString & replace) const
{
	if(find.Length() == 0)
	{
		FutureString newStr(m_string);
		return newStr;
	}

	f32 factor = (f32)replace.Length() / (f32)find.Length();
	if(factor < 1)
	{
		factor = 1;
	}
	if(find.Length() < 2)
	{
		factor *= 2;
	}
	u32 maxLength = (u32)(Length() * factor) + 2;
	wchar_t * buffer = new wchar_t[maxLength];
	u32 bufferIndex = 0;

	for(s32 i = Length() - find.Length(); i >= 0 && bufferIndex < (maxLength - 1); --i)
	{
		if(CharAt((u32)i) == find.CharAt(0))
		{
			u32 k = 1;
			u32 j = (u32)i + 1;
			for(; j < Length() && k < find.Length(); ++j, ++k)
			{
				if(CharAt(j) != find.CharAt(k))
				{
					break;
				}
			}
			if(k == find.Length())
			{
				for(k = 0; k < replace.Length(); ++k)
				{
					buffer[bufferIndex] = replace.CharAt(j);
					++bufferIndex;
				}
				i = (s32)j;
			}
			else
			{
				buffer[bufferIndex] = CharAt((u32)i);
				++bufferIndex;
			}
		}
		else
		{
			buffer[bufferIndex] = CharAt((u32)i);
			++bufferIndex;
		}
	}
	buffer[bufferIndex] = 0;
	FutureString newStr(buffer);
	return newStr;
}

void FutureString::Split(const FutureString & str, FutureArray<FutureString> * a) const
{
	FUTURE_ASSERT(str.Length() > 0 && a);
	s32 i = IndexOf(str);
	if(i >= 0)
	{
		if(i > 0)
		{
			a->Add(SubString(0, (u32)i));
		}
		FutureString rest = SubString((u32)i + str.Length());
		rest.Split(str, a);
	}
}

FutureString FutureString::SubString(u32 start, u32 count) const
{
	FUTURE_ASSERT(start >= 0 && start < Length() && start + count <= Length() && count != 0);

	FutureString strNew(m_string + start);
	if(count > 0)
	{
		strNew.ForceSize(count);
	}
	return strNew;
}

FutureString FutureString::Concat(const FutureString & str) const
{
	FutureString strNew;
	strNew = wcscat(m_string, str.WideString());
	return strNew;
}

*/
