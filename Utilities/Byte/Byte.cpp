#include "Byte.h"


Utilities::sBuffer::sBuffer()
{
	mByte = new BYTE[0];
	mSize = 0;
	mTrans = 0;
}

Utilities::sBuffer::sBuffer(sBuffer& _buffer)
{
	mByte = new BYTE[_buffer.mSize];
	mSize = _buffer.mSize;
	mTrans = _buffer.mTrans;
	memcpy_s(mByte, mSize, _buffer.mByte, mSize);
}

Utilities::sBuffer::~sBuffer()
{
	delete[] mByte;
}

void Utilities::sBuffer::Reset_Buffer(int _size)
{
	delete[] mByte;
	mByte = new BYTE[_size];
	mSize = _size;
	mTrans = 0;
}


void Utilities::sBuffer::Write(const bool& _bool)
{
	Write<const bool>(&_bool, (int)sizeof(bool));
}

void Utilities::sBuffer::Write(const char& _char)
{
	Write<const char>(&_char, (int)sizeof(char));
}

void Utilities::sBuffer::Write(const int& _int)
{
	Write<const int>(&_int, (int)sizeof(int));
}

void Utilities::sBuffer::Write(const __int64 _long)
{
	Write<const __int64>(&_long, (int)sizeof(__int64));
}

void Utilities::sBuffer::Write(const float& _float)
{
	Write<const float>(&_float, (int)sizeof(float));
}

void Utilities::sBuffer::Write(const double& _double)
{
	Write<const double>(&_double, (int)sizeof(double));
}

void Utilities::sBuffer::Write(const char* _string)
{
	//문자길이 + 문자열, 널값제외
	int len = strlen(_string);
	Write<int>(&len, (int)sizeof(int));
	Write<const char>(_string, len);
}

void Utilities::sBuffer::Write(BYTE* _byte, int _size)
{
	Write<int>(&_size, (int)sizeof(int));
	Write<BYTE>(_byte, _size);
}


bool Utilities::sBuffer::Read(OUT bool& _bool)
{
	return Read<bool>(&_bool, (int)sizeof(bool));
}

bool Utilities::sBuffer::Read(OUT int& _int)
{
	return Read<int>(&_int, (int)sizeof(int));
}

bool Utilities::sBuffer::Read(OUT __int64& _long)
{
	return Read<__int64>(&_long, (int)sizeof(__int64));
}

bool Utilities::sBuffer::Read(OUT char& _char)
{
	return Read<char>(&_char, (int)sizeof(char));
}

bool Utilities::sBuffer::Read(OUT float& _float)
{
	return Read<float>(&_float, (int)sizeof(float));
}

bool Utilities::sBuffer::Read(OUT double& _double)
{
	return Read<double>(&_double, (int)sizeof(double));
}

bool Utilities::sBuffer::Read(OUT char* _string)
{
	int len = 0;
	if(!Read<int>(&len, (int)sizeof(int))) return false;
	if(!Read<char>(_string, len)) return false;
	_string[len] = '\0';
	return true;
}

bool Utilities::sBuffer::Read(OUT BYTE* _byte)
{
	int size = 0;
	if (!Read<int>(&size, (int)sizeof(int))) return false;
	if (!Read<BYTE>(_byte, size)) return false;
	return true;
}

