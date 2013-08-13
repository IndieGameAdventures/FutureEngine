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

#ifndef FUTURE_CORE_UTIL_FILE_H
#define FUTURE_CORE_UTIL_FILE_H

#include <future/core/type/type.h>
#include <future/core/memory/memory.h>

#if FUTURE_PLATFORM_ANDROID
	class AAsset;
#elif FUTURE_PLATFORM_NATIVECLIENT
#	error Files aren't supported on native client at the moment
#	include <file_io.h>
#	include <file_system.h>
#else
#	include <stdio.h>
#endif

/*!
 *	\brief		File wrapper, handlers reading from and writing to a local file
 *
 *	\details 	This class acts as a simple wrapper around standard file operations. Because of the 
 *				differences in file operations on different systems this class is important for making
 *				clean and easy to understand file operations. Files can be opened in either read or 
 *				write mode but not both at the same time. It is recommended that a file be open for
 *				the smallest amount of time possible. Open, Read/Write, Close. It is also recommended
 *				that this class not be used directly but the developer should use FutureResourceManager
 *				to recieve data from files and FutureFileOutputStream to write to files. It is also
 *				important to note that FutureFile is not thread safe. An open file should only be read
 *				by one thread to ensure the file is read in the correct order each time. It is possible
 *				to read the entire file at once and split it up the memory into multiple stream readers
 *				and send reader to a different thread, making sure that each thread is accessing different
 *				memory buffers.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		August 2013
 */
class FutureFile
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureFile);
    
    //! FutureFile Constructor
	FutureFile();
	//! FutureFile Destructor
	virtual	 ~FutureFile();

	/*!	\brief		Opens the file at the provided location so that it can be read from
	 *	\details	The file path provided should be relative to the current working directory.
	 *				For example, most resources will be placed in the games 'assets' folder so
	 *				the file path would be something like 'assets/_234.ftr' (files compiled with
	 *				the resource compiler use the format <resource #>.ftr). 
	 *	\param[in]	file	The relative path to the file.
	 *	\return		True if the file was opened successfully, false otherwise.
	 */
	bool	 	OpenForRead(const char * file);

	/*!	\brief		Opens the file at the provided location so that it can be written to
	 *	\details	The file path provided should be relative to the current working directory.
	 *				For example, most resources will be placed in the games 'assets' folder so
	 *				the file path would be something like 'assets/_234.ftr' (files compiled with
	 *				the resource compiler use the format <resource #>.ftr). If append is true then
	 *				the file will not be cleared before writes begin so any data written will be
	 *				added on to the end of whatever is currently in the file.
	 *	\param[in]	file	The relative path to the file.
	 *	\param[in]	create	If the file does not exist and this flag is true, the file will attempt to be created 
	 *	\param[in]	append	If the file should be added to instead of emptied before written to.
	 *	\return		True if the file was opened successfully, false otherwise
	 */
	bool	 	OpenForWrite(const char * file, bool create = false, bool append = false);

	//! Closes the file. Must be called after finished reading or writing
	void		Close();

	//! Returns true if the file is currently open
	bool	 	IsOpen() const
	{ return m_open; }

	/*!	\brief		Reads the specified number of bytes from the file into dataOut
	 *	\details	Attempts to read the specified number of bytes from the file. If the end of the file
	 *				is reached, a number less than bytes will be returned to indicate the actual number 
	 *				of bytes read. 
	 *	\param[in]	bytes	The maximum number of bytes to read
	 *	\param[out]	dataOut	A pointer to a void array of at least bytes size.
	 *	\return		The actual number of bytes read
	 */
	u32	 		Read(u32 bytes, void * dataOut);

	/*!	\brief		Writes the specified number of bytes to the end of the file
	 *	\details	Writes the bytes contained in the data array to the end of the file. data must be at least bytes
	 *				long and will be written as binary data.
	 *	\param[in]	data	A pointer to a void array of at least bytes size.
	 *	\param[in]	bytes	The number of bytes to write from data
	 *	\return	True if the write succeeded, false if it did not
	 */
	bool 		Write(void * data, u32 bytes);

	/*!	\brief		Moved the cursor to the specified file index
	 *	\details	File indicies determine the current distance from the beginning of the file. This function
	 *				moves the current file index to the specified number of bytes from the beginning of the file.
	 *				If the file has been opened for writing, this will fill any extra space created with '\0' If
	 *				the file is open for reading, this will not seek past the end of the file.
	 *	\param[in]	bytes	The byte location from the beginning of the file to move to.
	 */
	void	 	Seek(u32 bytes);
	/*!	\brief		Moves the file cursor the specified number of bytes.
	 *	\details	Moves the current file index the specified number of bytes from the current location in the file.
	 *				This number can be negative and move the file cursor backwards but will not move past the beginning
	 *				of the file. If the file has been opened for writing, this will fill any extra space created with
	 *				'\0'. If the file is open for reading, this will not move past the end of the file.
	 *	\param[in]	bytes	The offset from the current file index to move
	 */
	void		Move(s32 bytes);

	//! Return the current file cursor location, equivalent to the number of bytes from the beginning of the file
	u32	 		Index() const
	{ return m_index; }
	//! The current number of bytes contained within the file
	u32	 		Size() const
	{ return m_size; }

private:

	bool	m_open;		//! True if the file is open and accessable
	u32	 	m_size;		//! The size, in bytes, of the file
	u32	 	m_index;	//! The current cursor index into the file

#if FUTURE_PLATFORM_ANDROID
	AAsset * 		m_asset;	//! Pointer to the Android Asset being accessed
#elif FUTURE_PLATFORM_NATIVECLIENT
#else
	FILE *	 		m_file;		//! Pointer to the OS File Handle
#endif
};

#endif