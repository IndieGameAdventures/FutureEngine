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
*	Implementation of FutureFile
*/

#include <future/core/util/file.h>

#if FUTURE_PLATFORM_ANDROID
#	include <android/asset_manager.h>
#elif FUTURE_PLATFORM_IOS || FUTURE_PLATFORM_OSX
#	include <CoreFoundation/CoreFoundation.h>
#endif

FutureFile::FutureFile()
	: m_open(false),
	  m_size(0),
	  m_index(0)
{}

FutureFile::~FutureFile()
{
	if(m_open)
	{
		Close();
	}
}

bool FutureFile::OpenForRead(const char * file)
{
	FUTURE_ASSERT(!m_open);

#if FUTURE_PLATFORM_ANDROID

	AAssets * assetManager = getAssets();
   	AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
    m_asset = AAssetManager_open(mgr, file, AASSET_MODE_UNKNOWN);
    if(!m_asset) 
    {
        return false;
    }
    m_size = AAsset_getLength(asset);
#elif FUTURE_PLATFORM_IPHONE || FUTURE_PLATFORM_MAC

    char nonConst[256];
	s32 length = strlen(file);
    memcpy(nonConst, file, length);

	char * path;
	char * fileName;
	char * ext;

	ext = strtchr(nonConst, '.' );			// Find the last '.'
	*ext = '\0';							// replace the '.' with '\0' so the file name will stop there
	++ext;									// move the extension string to the right start location
	fileName = strtchr(nonConst, '\\' );	// Do the same thing with the file name and path
	*fileName = '\0'
	++fileName;
	path = nonConst;

	CFURLRef url = CFBundleCopyResourceURL(CFBundleGetMainBundle(), 
		CFStringCreateWithCharacters(NULL, fileName, strlen(fileName)),
		CFStringCreateWithCharacters(NULL, ext, strlen(ext)),
		CFStringCreateWithCharacters(NULL, path, strlen(path));
	char fullPath[256];
	CFURLGetFileSystemRepresentation(url, true, fullPath, 256);
	CFRelease(url);

	m_file = fopen(fullPath, "rb");
	if(!m_file)
	{
		return false;
	}
	fseek(m_file, 0, SEEK_END);
	m_size = ftell(m_file);
	fseek(m_file, 0, SEEK_SET);
#else
	m_file = fopen(file, "rb");
	if(!m_file)
	{
		return false;
	}
	fseek(m_file, 0, SEEK_END);
	m_size = ftell(m_file);
	fseek(m_file, 0, SEEK_SET);
#endif
	m_open = true;
	return true;
}

bool FutureFile::OpenForWrite(const char * file, bool create, bool append)
{
	FUTURE_ASSERT(!m_open);
	m_index = 0;
	m_size = 0;

#if FUTURE_PLATFORM_ANDROID

	AAssets * assetManager = getAssets();
   	AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
    m_asset = AAssetManager_open(mgr, file, AASSET_MODE_UNKNOWN);
    if(!m_asset) 
    {
        return false;
    }
    m_size = AAsset_getLength(asset);
#elif FUTURE_PLATFORM_IPHONE || FUTURE_PLATFORM_MAC

    char nonConst[256];
	s32 length = strlen(file);
    memcpy(nonConst, file, length);

	char * path;
	char * fileName;
	char * ext;

	ext = strtchr(nonConst, '.' );			// Find the last '.'
	*ext = '\0';							// replace the '.' with '\0' so the file name will stop there
	++ext;									// move the extension string to the right start location
	fileName = strtchr(nonConst, '\\' );	// Do the same thing with the file name and path
	*fileName = '\0'
	++fileName;
	path = nonConst;

	CFURLRef url = CFBundleCopyResourceURL(CFBundleGetMainBundle(), 
		CFStringCreateWithCharacters(NULL, fileName, strlen(fileName)),
		CFStringCreateWithCharacters(NULL, ext, strlen(ext)),
		CFStringCreateWithCharacters(NULL, path, strlen(path));
	char fullPath[256];
	CFURLGetFileSystemRepresentation(url, true, fullPath, 256);
	CFRelease(url);

	if(append)
	{
		m_file = fopen(fullPath, "ab");
		if(!m_file && create)
		{
			m_file = fopen(fullPath, "wb");
		}
		else
		{
			fseek(m_file, 0, SEEK_END);
			m_size = ftell(m_file);
			fseek(m_file, 0, SEEK_SET);
		}
	}
	else
	{
		m_file = fopen(fullPath, "wb");
	}
	if(!m_file)
	{
		return false;
	}
#else
	if(append)
	{
		m_file = fopen(file, "ab");
		if(!m_file && create)
		{
			m_file = fopen(file, "wb");
		}
		else
		{
			fseek(m_file, 0, SEEK_END);
			m_size = ftell(m_file);
			fseek(m_file, 0, SEEK_SET);
		}
	}
	else
	{
		m_file = fopen(file, "wb");
	}
	if(!m_file)
	{
		return false;
	}
#endif
	m_open = true;
	return true;
}


void FutureFile::Close()
{
	FUTURE_ASSERT(m_open);

#if FUTURE_PLATFORM_ANDROID
    AAsset_close(m_asset);
    m_asset = NULL;
#else
	fclose(m_file);
	m_file = NULL;
#endif
	m_open = false;
	m_index = 0;
	m_size = 0;
}

u32	FutureFile::Read(u32 bytes, void * dataOut)
{
	FUTURE_ASSERT(m_open);
	FUTURE_ASSERT(m_index + bytes >= m_size);

#if FUTURE_PLATFORM_ANDROID
    AAsset_read(m_asset, dataOut, bytes);
#else
	bytes = fread(dataOut, 1, bytes, m_file);
#endif
	m_index += bytes;
    dataOut[bytes] = '\0';
    return bytes;
}

bool FutureFile::Write(void * data, u32 bytes)
{
	FUTURE_ASSERT(m_open && data && bytes > 0);
	u32 written = 0;

#if FUTURE_PLATFORM_ANDROID
    AAsset_write(m_asset, data, bytes);
    written = bytes;
#else
	written = fwrite(data, 1, bytes, m_file);
#endif
	m_index += written;
    return written == bytes;
}

void FutureFile::Seek(u32 bytes)
{
	FUTURE_ASSERT(m_open);

#if FUTURE_PLATFORM_ANDROID
    //AAsset_read(m_asset, dataOut, bytes);
#else
	fseek(m_file, bytes, SEEK_SET);
#endif
	m_index = bytes;
}

void FutureFile::Move(s32 bytes)
{
	FUTURE_ASSERT(m_open);

#if FUTURE_PLATFORM_ANDROID
    //AAsset_read(m_asset, dataOut, bytes);
#else
	fseek(m_file, bytes, SEEK_CUR);
#endif
	m_index += bytes;
}
