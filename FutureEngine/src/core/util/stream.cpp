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
*	Implementation of all Stream classes
*/

#include <future/core/util/stream.h>
#include <future/core/util/file.h>
#include <future/core/thread/thread.h>

FutureBufferedInputStream::FutureBufferedInputStream()
	: m_open(false),
	  m_bufferSize(0),
	  m_buffer(NULL)
{}


FutureBufferedInputStream::~FutureBufferedInputStream()
{
	FUTURE_ASSERT(!IsOpen());
}

void FutureBufferedInputStream::Close()
{
	FUTURE_ASSERT(IsOpen());

	m_buffer = NULL;
	m_bufferSize = 0;
	m_open = false;
}

u32 FutureBufferedInputStream::Read(u32 bytes, void * dataOut)
{
	u32 read = 0;
	while(bytes > 0)
	{
		CheckBuffer();
		if(m_bufferSize <= 0)
		{
			break;
		}
		u32 toRead = m_bufferSize > bytes ? bytes : m_bufferSize;

		if(dataOut)
		{
			memcpy(dataOut, m_buffer, toRead);
			dataOut = (void*)((u8*)dataOut + toRead);
		}
		m_bufferSize -= toRead;
		m_buffer += toRead;
		read += toRead;
		bytes -= toRead;
	}
	return read;
}
void FutureBufferedInputStream::Skip(u32 bytes)
{
	Read(bytes, NULL);
}

char FutureBufferedInputStream::ReadChar()
{
	char out;
	if(m_bufferSize >= 1)
	{
		out = *((char*)m_buffer);
		m_bufferSize -= 1;
		m_buffer += 1;
	}
	else
	{
		FUTURE_ASSERT(Read(1, &out) == 1);
	}
	return out;
}
bool FutureBufferedInputStream::ReadBool()
{
	bool out;
	if(m_bufferSize >= 1)
	{
		out = *((bool*)m_buffer);
		m_bufferSize -= 1;
		m_buffer += 1;
	}
	else
	{
		FUTURE_ASSERT(Read(1, &out) == 1);
	}
	return out;
}
u8 FutureBufferedInputStream::ReadU8()
{
	u8 out;
	if(m_bufferSize >= 1)
	{
		out = *((u8*)m_buffer);
		m_bufferSize -= 1;
		m_buffer += 1;
	}
	else
	{
		FUTURE_ASSERT(Read(1, &out) == 1);
	}
	return out;
}
u16 FutureBufferedInputStream::ReadU16()
{
	u16 out;
	if(m_bufferSize >= 2)
	{
		out = *((u16*)m_buffer);
		m_bufferSize -= 2;
		m_buffer += 2;
	}
	else
	{
		FUTURE_ASSERT(Read(2, &out) == 2);
	}
	return out;
}
u32 FutureBufferedInputStream::ReadU32()
{
	u32 out;
	if(m_bufferSize >= 4)
	{
		out = *((u32*)m_buffer);
		m_bufferSize -= 4;
		m_buffer += 4;
	}
	else
	{
		FUTURE_ASSERT(Read(4, &out) == 4);
	}
	return out;
}
s8 FutureBufferedInputStream::ReadS8()
{
	s8 out;
	if(m_bufferSize >= 1)
	{
		out = *((s8*)m_buffer);
		m_bufferSize -= 1;
		m_buffer += 1;
	}
	else
	{
		FUTURE_ASSERT(Read(1, &out) == 1);
	}
	return out;
}
s16 FutureBufferedInputStream::ReadS16()
{
	s16 out;
	if(m_bufferSize >= 2)
	{
		out = *((s16*)m_buffer);
		m_bufferSize -= 2;
		m_buffer += 2;
	}
	else
	{
		FUTURE_ASSERT(Read(2, &out) == 2);
	}
	return out;
}
s32 FutureBufferedInputStream::ReadS32()
{
	s32 out;
	if(m_bufferSize >= 4)
	{
		out = *((s32*)m_buffer);
		m_bufferSize -= 4;
		m_buffer += 4;
	}
	else
	{
		FUTURE_ASSERT(Read(4, &out) == 4);
	}
	return out;
}
f32 FutureBufferedInputStream::ReadF32()
{
	f32 out;
	if(m_bufferSize >= 4)
	{
		out = *((f32*)m_buffer);
		m_bufferSize -= 4;
		m_buffer += 4;
	}
	else
	{
		FUTURE_ASSERT(Read(4, &out) == 4);
	}
	return out;
}

// Be sure to free the returned memory when you are done with it
char * FutureBufferedInputStream::ReadString()
{
	u16 size = ReadU16();
	char * out = (char*)FUTURE_ALLOC(size + 1, "Buffered input stream string");
	FUTURE_ASSERT(Read(size, out) == size);
	out[size] = '/0';
	return out;
}
bool * FutureBufferedInputStream::ReadBoolArray(u32 * elementsOut)
{
	u16 size = ReadU16();
	bool * out = (bool*)FUTURE_ALLOC(size, "Buffered input stream bool array");
	FUTURE_ASSERT(Read(size, out) == size);
	*elementsOut = size;
	return out;
}
u8 * FutureBufferedInputStream::ReadU8Array(u32 * elementsOut)
{
	u16 size = ReadU16();
	u8 * out = (u8*)FUTURE_ALLOC(size, "Buffered input stream u8 array");
	FUTURE_ASSERT(Read(size, out) == size);
	*elementsOut = size;
	return out;
}
u16 * FutureBufferedInputStream::ReadU16Array(u32 * elementsOut)
{
	u16 size = ReadU16();
	u16 * out = (u16*)FUTURE_ALLOC(size * 2, "Buffered input stream u16 array");
	FUTURE_ASSERT(Read(size * 2, out) == size * 2);
	*elementsOut = size;
	return out;
}
u32 * FutureBufferedInputStream::ReadU32Array(u32 * elementsOut)
{
	u16 size = ReadU16();
	u32 * out = (u32*)FUTURE_ALLOC(size * 4, "Buffered input stream u32 array");
	FUTURE_ASSERT(Read(size * 4, out) == size * 4);
	*elementsOut = size;
	return out;
}
s8 * FutureBufferedInputStream::ReadS8Array(u32 * elementsOut)
{
	u16 size = ReadU16();
	s8 * out = (s8*)FUTURE_ALLOC(size, "Buffered input stream s8 array");
	FUTURE_ASSERT(Read(size, out) == size);
	*elementsOut = size;
	return out;
}
s16 * FutureBufferedInputStream::ReadS16Array(u32 * elementsOut)
{
	u16 size = ReadU16();
	s16 * out = (s16*)FUTURE_ALLOC(size * 2, "Buffered input stream s16 array");
	FUTURE_ASSERT(Read(size * 2, out) == size * 2);
	*elementsOut = size;
	return out;
}
s32 * FutureBufferedInputStream::ReadS32Array(u32 * elementsOut)
{
	u16 size = ReadU16();
	s32 * out = (s32*)FUTURE_ALLOC(size * 4, "Buffered input stream s32 array");
	FUTURE_ASSERT(Read(size * 4, out) == size * 4);
	*elementsOut = size;
	return out;
}
f32 * FutureBufferedInputStream::ReadFloatArray(u32 * elementsOut)
{
	u16 size = ReadU16();
	f32 * out = (f32*)FUTURE_ALLOC(size * 4, "Buffered input stream f32 array");
	FUTURE_ASSERT(Read(size * 4, out) == size) * 4;
	*elementsOut = size;
	return out;
}

bool FutureBufferedInputStream::ReadCheckSum()
{
	return ReadU32() == FUTURE_CHECKSUM;
}
void FutureBufferedInputStream::VerifyCheckSum()
{
	FUTURE_ASSERT(ReadCheckSum());
}

void FutureBufferedInputStream::CheckBuffer()
{
	if(m_bufferSize == 0 || m_buffer == NULL)
	{
		UpdateBuffer();
	}
}



FutureMemoryInputStream::FutureMemoryInputStream()
	: FutureBufferedInputStream(),
	  m_size(0),
	  m_data(NULL),
	  m_autoDelete(true)
{}
FutureMemoryInputStream::~FutureMemoryInputStream()
{}

bool FutureMemoryInputStream::Open(void * data, u32 size, bool autoDelete)
{
	FUTURE_ASSERT(!m_opne && m_data && m_size > 0);
	m_data = data;
	m_size = size;
	m_autoDelete = autoDelete;
	m_open = true;
}

void FutureMemoryInputStream::Close()
{
	FutureBufferedInputStream::Close();
	if(m_data && m_autoDelete)
	{
		delete m_data;
	}
	m_data = NULL;
	m_size = 0;
	m_open = false;
}


void FutureMemoryInputStream::UpdateBuffer()
{
	if(m_data && m_size > 0)
	{
		m_bufferSize = m_size;
		m_buffer = m_data;
		m_size = 0;
	}
	else
	{
		m_bufferSize = 0;
		m_buffer = NULL;
	}
}


void ReadFileAsync(void * data)
{
	FutureFileInputStream * stream = dynamic_cast<FutureFileInputStream*>(data);
	FUTURE_ASSERT(stream);
	stream->ProcessReadAsync();
}


FutureFileInputStream::FutureFileInputStream()
	: m_file(NULL),
	  m_chunkSize(4096),
	  m_chunk(NULL),
	  m_isEOF(false),
	  m_nextChunkSize(0),
	  m_nextChunk(NULL),
	  m_waitingForRead(false),
	  m_waitingForBuffer(false),
	  m_thread(NULL),
	  m_readAsync(true)
{}
FutureFileInputStream::~FutureFileInputStream()
{}

bool FutureFileInputStream::Open(const char * file, u32 chuckSize, bool async)
{
	FUTURE_ASSERT(!m_open && file && chunkSize > 0);
	
	m_file = new FutureFile();
	m_chunkSize = chunkSize;
#if FUTURE_ENABLE_MULTITHREADED
	m_readAsync = async;
#else
	m_readAsync = false;
#endif
	m_isEOF = false;
	m_waitingForBuffer = false;
	m_waitingForRead = false;

	bool result = m_file->OpenForRead(file);
	if(result)
	{
		m_chunk = FUTURE_ALLOC(m_chunkSize, "File Input Stream Buffer");
		FUTURE_ASSERT(m_chunk);
		if(m_readAsync)
		{
			m_nextChunk = FUTURE_ALLOC(m_chunkSize, "File Input Stream Buffer");
			FUTURE_ASSERT(m_nextChunk);
			m_thread = IFutureThread::CreateThread();
			FUTURE_ASSERT(m_thread);
			m_thread->Start(ReadFileAsync, this);
		}
	}
	return result;
}
void FutureFileInputStream::Close()
{
	if(m_thread)
	{
		m_isEOF = true;
		m_thread->Join();
		IFutureThread::DestroyThread(m_thread);
		m_thread = NULL;
	}
	FutureBufferedInputStream::Close();
	if(m_file)
	{
		if(m_file->IsOpen())
		{
			m_file->Close();
		}
		delete m_file;
		m_file = NULL;
	}
	if(m_chunk)
	{
		FUTURE_FREE(m_chunk);
		m_chunk = NULL;
	}
	if(m_nextChunk)
	{
		FUTURE_FREE(m_nextChunk);
		m_nextChunk = NULL;
	}
}

void FutureFileInputStream::ProcessReadAsync()
{
	while(!m_isEOF)
	{
		while(m_waitingForBuffer)
		{
			m_thread->Sleep(1);
			if(m_isEOF)
			{
				return;
			}
		}
		m_waitingForRead = true;
		FUTURE_ASSERT(m_open && m_file && m_nextChunk)
		m_nextChunkSize = m_file->Read(m_chunkSize, m_nextChunk);
		m_waitingForBuffer = true;
		m_waitingForRead = false;
	}
}

void FutureFileInputStream::UpdateBuffer()
{
	FUTURE_ASSERT(m_open && m_file && m_chunk)

	if(m_isEOF)
	{
		m_bufferSize = 0;
		m_buffer = NULL;
		return;
	}

	if(m_readAsync)
	{
		while(m_waitingForRead)
		{
			Sleep(1);
		}
		if(m_nextChunkSize < m_chunkSize)
		{
			m_isEOF = true;
		}
		memcpy(m_chunk, m_nextChunk, m_nextChunkSize);
		m_waitingForBuffer = false;
		m_bufferSize = m_chunk;
		m_buffer = m_chunk;
	}
	else
	{
		m_bufferSize = m_file->Read(m_chunkSize, m_chunk);
		m_buffer = m_chunk;
		if(m_bufferSize < m_chunkSize)
		{
			m_isEOF = true;
		}
	}
}



FutureBufferedOutputStream::FutureBufferedOutputStream()
	: m_open(false)
{}
FutureBufferedOutputStream::~FutureBufferedOutputStream()
{
	FUTURE_ASSERT(!m_open);
}


bool FutureBufferedOutputStream::Write(const void * data, u32 bytes)
{
	return WriteInternal(data, bytes);
}
bool FutureBufferedOutputStream::Skip(u32 bytes)
{
	return WriteInternal(NULL, bytes);
}

bool FutureBufferedOutputStream::Write(char data)
{
	return WriteInternal(&data, 1);
}
bool FutureBufferedOutputStream::Write(bool data)
{
	return WriteInternal(&data, 1);
}
bool FutureBufferedOutputStream::Write(u8 data)
{
	return WriteInternal(&data, 1);
}
bool FutureBufferedOutputStream::Write(u16 data)
{
	return WriteInternal(&data, 2);
}
bool FutureBufferedOutputStream::Write(u32 data)
{
	return WriteInternal(&data, 4);
}
bool FutureBufferedOutputStream::Write(s8 data)
{
	return WriteInternal(&data, 1);
}
bool FutureBufferedOutputStream::Write(s16 data)
{
	return WriteInternal(&data, 2);
}
bool FutureBufferedOutputStream::Write(s32 data)
{
	return WriteInternal(&data, 4);
}
bool FutureBufferedOutputStream::Write(f32 data)
{
	return WriteInternal(&data, 4);
}

bool FutureBufferedOutputStream::Write(const * char string)
{
	u16 length = (u16)strlen(string);
	Write(length);
	return WriteInternal(string, length - 1);
}
bool FutureBufferedOutputStream::Write(const * bool data, u32 elements)
{
	Write((u16)elements);
	return WriteInternal(data, elements * 1);
}
bool FutureBufferedOutputStream::Write(const * u8 data, u32 elements)
{
	Write((u16)elements);
	return WriteInternal(data, elements * 1);
}
bool FutureBufferedOutputStream::Write(const * u16 data, u32 elements)
{
	Write((u16)elements);
	return WriteInternal(data, elements * 2);
}
bool FutureBufferedOutputStream::Write(const * u32 data, u32 elements)
{
	Write((u16)elements);
	return WriteInternal(data, elements * 4);
}
bool FutureBufferedOutputStream::Write(const * s8 data, u32 elements)
{
	Write((u16)elements);
	return WriteInternal(data, elements * 1);
}
bool FutureBufferedOutputStream::Write(const * s16 data, u32 elements)
{
	Write((u16)elements);
	return WriteInternal(data, elements * 2);
}
bool FutureBufferedOutputStream::Write(const * s32 data, u32 elements)
{
	Write((u16)elements);
	return WriteInternal(data, elements * 4);
}
bool FutureBufferedOutputStream::Write(const * f32 data, u32 elements)
{
	Write((u16)elements);
	return WriteInternal(data, elements * 4);
}

bool FutureBufferedOutputStream::WriteCheckSum()
{
	return Write((u32)FUTURE_CHECKSUM);
}



FutureMemoryOutputStream::FutureMemoryOutputStream()
	: FutureBufferedOutputStream(),
	  m_data()
{}
FutureMemoryOutputStream::~FutureMemoryOutputStream()
{}

bool FutureMemoryOutputStream::Open()
{
	FUTURE_ASSERT(!m_open);
	m_data.Clear();
	m_open = true;
}
void FutureMemoryOutputStream::Close()
{
	FUTURE_ASSERT(m_open);
	m_data.Clear();
	FutureBufferedOutputStream::Close();
}

u32 FutureMemoryOutputStream::Size()
{
	return m_data.Size();
}
bool FutureMemoryOutputStream::Flush()
{
	return true;
}

bool FutureMemoryOutputStream::WriteInternal(const void * data, u32 size)
{
	FUTURE_ASSERT(m_open);
	u32 preSize = m_data.Size();
	if(data == NULL)
	{
		m_data.SetSize(m_data.Size() + size);
	}
	else
	{
		m_data.AddMultiple((u8*)data, size);
	}
	return (preSize + size) == m_data.Size();
}

const void * FutureMemoryOutputStream::GetData()
{
	return m_data.a();
}

void FutureMemoryOutputStream::ClearBuffer()
{
	m_data.Clear();
}


FutureFileOutputStream::FutureFileOutputStream()
	: FutureMemoryOutputStream(),
	  m_file(NULL),
	  m_size(0)
{}
FutureFileOutputStream::~FutureFileOutputStream()
{}

bool FutureFileOutputStream::Open(const char * file, bool append = false)
{
	FutureMemoryOutputStream::Open();

	FUTURE_ASSERT(file );
	
	m_file = new FutureFile();
	m_size = 0;
	return m_file->OpenForWrite(file, append);
}

void FutureFileOutputStream::Close()
{
	FutureMemoryOutputStream::Close();

	if(m_file)
	{
		if(m_file->IsOpen())
		{
			m_file->Close();
		}
		delete m_file;
		m_file = NULL;
	}
	m_size = 0;
}

u32 FutureFileOutputStream::Size()
{
	return m_size + FutureMemoryOutputStream::Size();
}

bool FutureFileOutputStream::Flush()
{
	u32 size = FutureMemoryOutputStream::Size();
	bool result = m_file->Write(FutureMemoryOutputStream::GetData(), size);
	if(result)
	{
		m_size += size;
		FutureMemoryOutputStream::ClearBuffer();
	}
	return result;
}

