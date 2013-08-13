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

#ifndef FUTURE_CORE_UTIL_STREAM_H
#define FUTURE_CORE_UTIL_STREAM_H

#include <future/core/type/type.h>
#include <future/core/memory/memory.h>

// Forward Declares
class FutureFile;
class IFutureThread;

/*!
 *	\brief		An Input Stream for reading data
 *
 *	\details 	An input stream is a buffered data reader that pulls down a certain amount of data from a
 *				source and allows the rest of the program to interact with that data. Once the current buffer
 *				is fully read, the buffer will be filled from the stream again. This class provides a set of
 *				generic methods for reading and interpreting data from the stream. It must be instantiated as
 *				a valid sub class with the function update buffer implemented. Not that this class assumed the
 *				input steam was created using an FutureBufferedOutputStream. Reading a single data element or calling the
 *				generic Read and Skip functions should work properly on any stream, regardless of the origin.
 *				In order to get the correct values from ReadString and Read*Array the input stream must be size
 *				prefixed meaning the number of elements in the array is written as a 16 bit unsigned integer 
 *				before the array of elements. It is important to note that Input Streams are meant to be read
 *				linearly by one thread, because of this, they are not thread safe to reduce the overhead caused
 *				by enforcing thread safety. Each stream should only ever be touched by one thread throughout
 *				it's entire life.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		August 2013
 */
class FutureBufferedInputStream
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureBufferedInputStream);

    //! FutureBufferedInputStream Constructor, should not be called directly
	FutureBufferedInputStream();
	//! FutureBufferedInputStream Destructor ensures that all buffers and streams and released and closed
	virtual	 ~FutureBufferedInputStream();

	//! Closes the current stream and releases the current buffer
	virtual void Close() = 0;

	//! Return true if this stream is open and able to be read
	bool	 	IsOpen() const
	{ return m_open; }

	/*!	\brief		Reads the specified number of bytes from the current stream into dataOut
	 *	\details	Attempts to read the specified number of bytes from the current buffer. If this would
	 *				require reading past the end of the stream, FutureBufferedInputStream will update it's buffer from
	 *				the current stream and continue to read. If the end of the stream is reached, a number 
	 *				less than bytes will be returned to indicate the actual number of bytes read. Usually
	 *				reading an incorrect number of bytes indicates an error.
	 *	\param[in]	bytes	The maximum number of bytes to read
	 *	\param[out]	dataOut	A pointer to a void array of at least bytes size.
	 *	\return	The actual number of bytes read
	 */
	u32	 		Read(u32 bytes, void * dataOut);
	/*!	\brief		Skips a certain number of bytes, be careful as there is no way to go backwards
	 *	\param[in]	bytes	The number of bytes to skip
	 */
	void	 	Skip(u32 bytes);

	//!	Reads the next byte from the stream and returns it as a bool
    bool		ReadBool();
	//!	Reads the next byte from the stream and returns it as an unsigned 8 bit value
    u8			ReadU8();
	//!	Reads the next 2 bytes from the stream, rearranged them to fit the current endianness and returns an unsigned 16 bit value
    u16			ReadU16();
	//!	Reads the next 4 bytes from the stream, rearranged them to fit the current endianness and returns an unsigned 32 bit value
    u32			ReadU32();
	//!	Reads the next byte from the stream and returns it as a signed 8 bit value
    s8			ReadS8();
	//!	Reads the next 2 bytes from the stream, rearranged them to fit the current endianness and returns a signed 16 bit value
    s16			ReadS16();
	//!	Reads the next 4 bytes from the stream, rearranged them to fit the current endianness and returns a signed 32 bit value
    s32			ReadS32();
	//!	Reads the next 4 bytes from the stream, rearranged them to fit the current endianness and returns a 32 bit floating pointer value
    f32			ReadF32();

	/*!	\brief		Reads a string (char array) from the current stream.
	 *	\details	The resulting string will be a null terminated multibyte character array.
	 *				The string must be freed by the caller with FUTURE_FREE() 
	 *	\return		A character array that must be freed by the caller with FUTURE_FREE
	 */
	char *		ReadString();
	/*!	\brief		Reads a boolean array from the current stream.
	 *	\details	The array must be freed by the caller with FUTURE_FREE() 
	 *	\param[out]	elementsOut	Places the total number of boolean values read in elementsOut
	 *	\return		A boolean array that must be freed by the caller with FUTURE_FREE
	 */
    bool *		ReadBoolArray(u32 * elementsOut);
	/*!	\brief		Reads an unsigned 8-bit int array from the current stream.
	 *	\details	The array must be freed by the caller with FUTURE_FREE() 
	 *	\param[out]	elementsOut	Places the total number of unsigned 8-bit values read in elementsOut
	 *	\return		An unsigned 8-bit int array that must be freed by the caller with FUTURE_FREE
	 */
    u8 *		ReadU8Array(u32 * elementsOut);
	/*!	\brief		Reads an unsigned 16-bit int array from the current stream.
	 *	\details	The array must be freed by the caller with FUTURE_FREE() 
	 *	\param[out]	elementsOut	Places the total number of unsigned 16-bit values read in elementsOut
	 *	\return		An unsigned 16-bit int array that must be freed by the caller with FUTURE_FREE
	 */
    u16 *		ReadU16Array(u32 * elementsOut);
	/*!	\brief		Reads an unsigned 32-bit int array from the current stream.
	 *	\details	The array must be freed by the caller with FUTURE_FREE() 
	 *	\param[out]	elementsOut	Places the total number of unsigned 32-bit values read in elementsOut
	 *	\return		An unsigned 32-bit int array that must be freed by the caller with FUTURE_FREE
	 */
    u32 *		ReadU32Array(u32 * elementsOut);
	/*!	\brief		Reads an 8-bit int array from the current stream.
	 *	\details	The array must be freed by the caller with FUTURE_FREE() 
	 *	\param[out]	elementsOut	Places the total number of 8-bit int values read in elementsOut
	 *	\return		An 8-bit int array that must be freed by the caller with FUTURE_FREE
	 */
    s8 *		ReadS8Array(u32 * elementsOut);
	/*!	\brief		Reads a 16-bit int array from the current stream.
	 *	\details	The array must be freed by the caller with FUTURE_FREE() 
	 *	\param[out]	elementsOut	Places the total number of 16-bit int values read in elementsOut
	 *	\return		A 16-bit int array that must be freed by the caller with FUTURE_FREE
	 */
    s16 *		ReadS16Array(u32 * elementsOut);
	/*!	\brief		Reads a 32-bit int array from the current stream.
	 *	\details	The array must be freed by the caller with FUTURE_FREE() 
	 *	\param[out]	elementsOut	Places the total number of 32-bit int values read in elementsOut
	 *	\return		A 32-bit int array that must be freed by the caller with FUTURE_FREE
	 */
    s32 *		ReadS32Array(u32 * elementsOut);
	/*!	\brief		Reads a floating point array from the current stream.
	 *	\details	The array must be freed by the caller with FUTURE_FREE() 
	 *	\param[out]	elementsOut	Places the total number of float values read in elementsOut
	 *	\return		An array or floats that must be freed by the caller with FUTURE_FREE
	 */
    f32 *		ReadFloatArray(u32 * elementsOut);

	/*!	\brief		Reads a 32 bit check sum value from the stream
	 *	\details	The value read must have been written with FutureBufferedOutputStream::WriteCheckSum.
	 *				If the u32 read in does not match the expected check sum then either there
	 *				is data corruption or the file was not read in the same order it was written in.
	 *	\return		True if the checksum read matches the expected checksum, false otherwise
	 */
    bool		ReadCheckSum();
	/*!	\brief		Reads a 32 bit checksum from the stream and asserts if is it not valid
	 *	\details	Very similar to ReadCheckSum except that this function will fire an assert
	 *				if the checksum is not valid. 
	 */
    void		VerifyCheckSum();

protected:

	/*	\brief	Checks if the buffer is empty and calls UpdateBuffer if it is
	 */
	void			CheckBuffer();
	/*	\brief		Updates the buffer.
	 *	\details	This function must not called unless the buffer is empty. All sub-classes must implement this.
	 */
	virtual void 	UpdateBuffer() = 0;

	bool		m_open;	//! Determines if the stream is currently open and able to be read

	u32	 		m_bufferSize;	//! The number of bytes left in the current buffer
	u8 *		m_buffer;		//! A pointer to the next element to read from the buffer
};


/*!
 *	\brief		An Input Stream for reading data from memory
 *
 *	\details 	Works as a very small wrapper around FutureBufferedInputStream. Opened with a memory buffer
 *				passes the entire buffer to FutureBufferedInputStream to be read.
 *
 *				It is important to note that Input Streams are meant to be read linearly by one thread,
 *				because of this, they are not thread safe to reduce the overhead caused by enforcing thread 
 *				safety. Each stream should only ever be touched by one thread throughout it's entire life.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		August 2013
 */
class FutureMemoryInputStream : public FutureBufferedInputStream
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureMemoryInputStream);

	//! FutureMemoryInputStream Constructor
	FutureMemoryInputStream();
	//! FutureMemoryInputStreamDestructor
	virtual ~FutureMemoryInputStream();

	/*!	\brief		Opens this stream with the provided data
	 *	\details	Takes in the provided data and size and stores them. When update buffer is called
	 *				for the first time, FutureMemoryInputStream will send the entire data pool to be buffered.
	 *	\param[in]	data	A pointer to the data to be read by this stream
	 *	\param[in]	size	The size, in bytes, of the data array
	 *	\param[in]	autoDelete	If this value is true, the data array will be delete when the stream is closed. It must be freed elsewhere if this is false.
	 *	\return		True if the stream was opened successfully, false otherwise
	 */
	bool			Open(void * data, u32 size, bool autoDelete = true);
	//! Closes the stream and deletes the data buffer if autoDelete is true
	virtual void	Close();

protected:

	/*!	\brief		Sends the provided data to the FutureBufferedInputStream 
	 *	\details	The first time this is called with a new stream, FutureMemoryInputStream will send the entire
	 *				data to the FutureBufferedInputStream buffer to be processed. Any additional calls will do nothing.
	 */
	virtual void UpdateBuffer();

	u32 	m_size;			//! The size in bytes of the input memory stream
	void * 	m_data;			//! The memory data to read from
	bool	m_autoDelete;	//! True if this stream should delete the memory data when it is closed
};


/*!
 *	\brief		An Input Stream for streaming data from a file
 *
 *	\details 	Works as a very wrapper around FutureBufferedInputStream. FutureFileInputStream locates and opens a
 *				file then reads in small chunks of the file at a time, passing the data on to the buffered reader while
 *				it loads the next chunk. This asynchronous loading should allow for reading to happen quickly, with very
 *				little time spent getting data form the file on the same thread that is being used for reading. There may
 *				be some stalling as reading the file may take longer than proccessing the data. But hopefully not much.
 *
 *				It is important to note that Input Streams are meant to be read linearly by one thread,
 *				because of this, they are not thread safe to reduce the overhead caused by enforcing thread 
 *				safety. Each stream should only ever be touched by one thread throughout it's entire life.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		August 2013
 */
class FutureFileInputStream : public FutureBufferedInputStream
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureFileInputStream);

	//! FutureFileInputStream Constructor
	FutureFileInputStream();
	//! FutureMemoryInputStreamDestructor
	virtual ~FutureFileInputStream();

	/*!	\brief		Opens an input stream to the provided file
	 *	\details	Opens the file at the provided location and attempts to stream data from the file.
	 *	\param[in]	file	The file name and location to read from
	 *	\param[in]	chunkSize	The size, in bytes, of each buffered chunk to read from the file. Defaulted to 4k chunks
	 *	\param[in]	async	True if the file should be read on a seperate thread or false to read on the current thread
	 *	\return		True if the file stream was opened successfully, false otherwise
	 */
	bool			Open(const char * file, u32 chunkSize = 4096, bool async = true);
	//! Closes the stream and deletes the data buffer if autoDelete is true
	virtual void	Close();


	/*!	\brief		Reads the file, one chunk at a time, into the secondary buffer
	 *	\details	Should not be called, for internal use only! If this function is
	 *				called on the same thread the buffer is being processed by, it will
	 *				result in a deadlock. Do not call this function.
	 */
	 void	ProcessReadAsync();

protected:

	/*!	\brief		Reads data from the file and sends it to the FutureBufferedInputStream buffer
	 *	\details	If m_readAsync is true this function will swap the current buffer with the next buffer
	 *				and begin reading the next chunk. If the next chunk is not finished being read, this
	 *				function will block until it has finished. If m_readAsync is false, this function will
	 *				read from the file directly and block until the file chunk has been read.
	 */
	virtual void UpdateBuffer();

	/*!	\brief		Reads a chunk of data from the file
	 */
	 void	ReadChunk();

	FutureFile * 	m_file;				//! The file begin streamed
	u32				m_chunkSize;		//! The size of each buffer chunk
	void *			m_chunk;			//! A pointer to the current buffered chunk.

	u32				m_nextChunkSize		//! The size of the next buffered chunk
	void *			m_nextChunk;		//! A pointer to the chunk currently being read in

	volatile bool	m_isEOF;			//! True if the end of the file was reached.
	volatile bool	m_waitingForRead;	//! True if a chunk is currently being read
	volatile bool	m_waitingForBuffer;	//! True if the chunk has been read but the FutureBufferedInputStream has not requested it yet

	bool			m_readAsync			//! True id the stream should read asynchronously
	IFutureThread *	m_thread;			//!	The thread used to read the file
};




/*!
 *	\brief		An Output Stream for writing data to a buffer
 *
 *	\details 	This abstract class writes binary data to a buffer. The buffer is then written out to it's final
 *				destination depending what super class is being used. Data is written using the many Write functions
 *				then exported using the Flush command. Data written by this class is expected to be read back using
 *				a FutureBufferedInputStream, though text can be written directly using a wrapper class. All
 *				write functions return a boolean indicating if the write was successful or not. There are several
 *				reasons a write might fail. For file streams, the file may have been opened in another program and
 *				is now locked. In other streams the buffer may be full, the network stream was closed, or some other
 *				system function is blocking writes at the moment. Best thing to do is close the stream and re-open it
 *				if no information is available in the error log.
 *
 *				It is important to note that Output Streams are meant to be written linearly by one thread,
 *				because of this, they are not thread safe to reduce the overhead caused by enforcing thread 
 *				safety. Each stream should only ever be touched by one thread throughout it's entire life.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		August 2013
 */
class FutureBufferedOutputStream
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureBufferedOutputStream);
    
    //! FutureBufferedOutputStream Constructor, should not be called directly
	FutureBufferedOutputStream();
	//! FutureBufferedInputStream Destructor ensures that all buffers and streams and released and closed
	virtual	 ~FutureBufferedOutputStream();

	//! Flushes any remaining data, closes the stream, and deletes any buffers.
	virtual void Close();

	//! Returns true if this stream is open and able to be written to
	bool	 	IsOpen() const
	{ return m_open; }

	//! Returns the current size of the stream in bytes; this includes any current buffers.
	virtual u32	Size() = 0;

	/*!	\brief		Writes the specified number of bytes into the buffer.
	 *	\details	Writes the bytes contained in the data array to the current buffer. data must be at least bytes
	 *				long and will be written as binary data.
	 *	\param[in]	data	A pointer to a void array of at least bytes size.
	 *	\param[in]	bytes	The number of bytes to write from data
	 *	\return	True if the write succeeded, false if it did not
	 */
	bool 		Write(const void * data, u32 bytes);

	/*!	\brief		Skips the provided number of bytes.
	 *	\details	Writes '/0' to the stream until the number of bytes specified have been written. Useful for adding alignment buffers
	 *	\param[in]	bytes	The number of empty bytes to write to the buffer.
	 *	\return	True if the write succeeded, false if it did not
	 */
	bool		Skip(u32 bytes);

	//! \brief	Attempts to write a single character to the output buffer.
	//! \param[in]	data The character to write
	//! \returns True if the write succeeds
	bool		Write(char data);
	//! \brief	Attempts to write a single boolean to the output buffer.
	//! \param[in]	data The boolean to write
	//! \returns True if the write succeeds
	bool		Write(bool data);
	//! \brief	Attempts to write an unsigned 8-bit value to the output buffer.
	//! \param[in]	data The unsigned int to write
	//! \returns True if the write succeeds
	bool		Write(u8 data);
	//! \brief	Attempts to write an unsigned 16-bit value to the output buffer.
	//! \param[in]	data The unsigned int to write
	// \returns True if the write succeeds
	bool		Write(u16 data);
	//! \brief	Attempts to write an unsigned 32-bit value to the output buffer.
	//! \param[in]	data The unsigned int to write
	//! \returns True if the write succeeds
	bool		Write(u32 data);
	//! \brief	Attempts to write a signed 8-bit value to the output buffer.
	//! \param[in]	data The int to write
	//! \returns True if the write succeeds
	bool		Write(s8 data);
	//! \brief	Attempts to write a signed 16-bit value to the output buffer.
	//! \param[in]	data The int to write
	//! \returns True if the write succeeds
	bool		Write(s16 data);
	//! \brief	Attempts to write a signed 32-bit value to the output buffer.
	//! \param[in]	data The int to write
	//! \returns True if the write succeeds
	bool		Write(s32 data);
	//! \brief	Attempts to write a 32 bit floating point value to the output buffer.
	//! \param[in]	data The float to write
	//! \returns True if the write succeeds
	bool		Write(f32 data);

	//! \brief	Attempts to write the null terminated string to the output buffer.
	//! \param[in]	string A null-terminated character array to write to the output buffer
	//! \returns True if the write succeeds
	bool		Write(const * char string);
	//! \brief	Attempts to write a boolean array to the output buffer.
	//! \param[in]	data A pointer to an array of boolean values to write to the buffer
	//!	\param[in]	elements	The number of boolean values in the data array
	//! \returns True if the write succeeds
	bool		Write(const * bool data, u32 elements);
	//! \brief	Attempts to write a u8 array to the output buffer.
	//! \param[in]	data A pointer to an array of u8 values to write to the buffer
	//!	\param[in]	elements	The number of u8 values in the data array
	//! \returns True if the write succeeds
	bool		Write(const * u8 data, u32 elements);
	//! \brief	Attempts to write a u16 array to the output buffer.
	//! \param[in]	data A pointer to an array of u16 values to write to the buffer
	//!	\param[in]	elements	The number of u16 values in the data array
	//! \returns True if the write succeeds
	bool		Write(const * u16 data, u32 elements);
	//! \brief	Attempts to write a u32 array to the output buffer.
	//! \param[in]	data A pointer to an array of u32 values to write to the buffer
	//!	\param[in]	elements	The number of u32 values in the data array
	//! \returns True if the write succeeds
	bool		Write(const * u32 data, u32 elements);
	//! \brief	Attempts to write a s8 array to the output buffer.
	//! \param[in]	data A pointer to an array of s8 values to write to the buffer
	//!	\param[in]	elements	The number of s8 values in the data array
	//! \returns True if the write succeeds
	bool		Write(const * s8 data, u32 elements);
	//! \brief	Attempts to write a s16 array to the output buffer.
	//! \param[in]	data A pointer to an array of s16 values to write to the buffer
	//!	\param[in]	elements	The number of s16 values in the data array
	//! \returns True if the write succeeds
	bool		Write(const * s16 data, u32 elements);
	//! \brief	Attempts to write a s32 array to the output buffer.
	//! \param[in]	data A pointer to an array of s32 values to write to the buffer
	//!	\param[in]	elements	The number of s32 values in the data array
	//! \returns True if the write succeeds
	bool		Write(const * s32 data, u32 elements);
	//! \brief	Attempts to write a float array to the output buffer.
	//! \param[in]	data A pointer to an array of float values to write to the buffer
	//!	\param[in]	elements	The number of float values in the data array
	//! \returns True if the write succeeds
	bool		Write(const * f32 data, u32 elements);

	//! \brief	Attempts to write a u32 checksum value to the output buffer.
	//! \returns True if the write succeeds
    bool		WriteCheckSum();

	//! \brief	Attempts to write the current buffer to the output stream.
	//! \returns True if the write succeeds
    virtual bool	Flush() = 0;

protected:

	//! \brief	Used by sub-classes to handle actually writing the binary data
	//! \param[in]	data	A pointer to a void array of at least bytes size.
	//! \param[in]	size	The number of bytes to write from data
	//! \return	True if the write succeeded, false if it did not
	virtual bool WriteInternal(const void * data, u32 size) = 0;

	bool		m_open;	//! True if this stream is currently open and able to be written to.
};



/*!
 *	\brief		An Output Stream for writing data to a memory buffer
 *
 *	\details 	The simplest of output streams, this class simply creates a byte array in memory and
 *				writes the provided data to it, incrementing it's position in the buffer with each write.
 *				This writer will dynamically expand itself to ensure the buffer is large enough to for the
 *				current write request.
 *
 *				It is important to note that Output Streams are meant to be written linearly by one thread,
 *				because of this, they are not thread safe to reduce the overhead caused by enforcing thread 
 *				safety. Each stream should only ever be touched by one thread throughout it's entire life.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		August 2013
 */
class FutureMemoryOutputStream : public FutureBufferedOutputStream
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureMemoryOutputStream);

    //! FutureMemoryOutputStream Constructor
	FutureMemoryOutputStream();
	//! FutureMemoryOutputStream Destructor ensures that all buffers and streams and released and closed
	virtual ~FutureMemoryOutputStream();

	//! Creates a new expandable memory buffer to write to.
	bool			Open();
	//! Closes and deletes the above created memory buffer.
	virtual void	Close();
	
	//! Returns the number of bytes currently written to the stream
	virtual u32		Size();

	//! Does nothing as the data is already written to it's final destination
	virtual bool	Flush();

	//! Returns a pointer to the internal data.
	const void *	GetData();

	//! Clears the memory buffer
	void			ClearBuffer();
protected:

	//! \brief	Adds the data to the internal data array
	//! \param[in]	data	A pointer to a void array of at least bytes size.
	//! \param[in]	size	The number of bytes to write from data
	//! \return	True if the write succeeded, false if it did not
	virtual bool WriteInternal(const void * data, u32 size);

	FutureArray<u8>	m_data;	//! The array of bytes being written to.
};


/*!
 *	\brief		An Output Stream for writing data to an extenal file
 *
 *	\details 	This classes expands on the functionality of FutureMemoryOutputStream by using that classes
 *				memory buffer as a file buffer. Writes are made to the FutureMemoryOutputStream buffer until
 *				Flush is called. At which point, the contents of the buffer are synchronously written to the
 *				file. Then the buffer has been completely written out, it is empties to allow for new data to
 *				be written. It is suggested to only flush the buffer once to avoid multiple writes to the file.
 *
 *				It is important to note that Output Streams are meant to be written linearly by one thread,
 *				because of this, they are not thread safe to reduce the overhead caused by enforcing thread 
 *				safety. Each stream should only ever be touched by one thread throughout it's entire life.
 *				
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		August 2013
 */
class FutureFileOutputStream : public FutureMemoryOutputStream
{
public:
	FUTURE_DECLARE_MEMORY_OPERATORS(FutureFileOutputStream);

    //! FutureFileOutputStream Constructor
	FutureFileOutputStream();
	//! FutureFileOutputStream Destructor ensures that all buffers and streams and released and closed
	virtual ~FutureFileOutputStream();

	//! Opens the provided file for writing
	//! \param[in]	file	The name and location of the file to be written to
	//! \param[in]	append	Determines if the stream should append writes to the end of the file or delete the current content before making any writes
	bool			Open(const char * file, bool append = false);
	//! Flushes and remaining data then closes the file and deletes all buffers
	virtual void	Close();
	
	//! Returns the number of bytes that have been written to the file or to a buffer
	virtual u32		Size();

	//! Takes all data currently in the memory buffer and writes it out to the file, then empties the buffer
	virtual bool	Flush();

protected:

	u32				m_size;	//! The current number of bytes written to the file
	FutureFile * 	m_file;	//! A pointer to the file object being written to
};

#endif