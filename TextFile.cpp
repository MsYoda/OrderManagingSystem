#pragma once
#include "TextFile.h"

template<typename T>
TextFile<T>::TextFile(QString filename) : File(filename)
{}

template<typename T>
void TextFile<T>::SetFileName(QString fname)
{
	this->fileName = fname;
}

template<typename T>
void TextFile<T>::OpenForReading()
{
	char* str = this->fileName.ToChars();
	this->textReadStream.open(str, std::ios::in);
	this->textWriteStream.close();
}

template<typename T>
void TextFile<T>::OpenForWriting()
{
	char* str = this->fileName.ToChars();
	this->textWriteStream.open(str, std::ios::out);
	this->textReadStream.close();
}

template<typename T>
T TextFile<T>::ReadObj()
{
	T obj;
	if (!this->textReadStream.eof())
		this->textReadStream >> obj;
	return obj;
}

template<typename T>
void TextFile<T>::WriteObj(T& obj)
{
	if (!this->textWriteStream.eof())
		this->textWriteStream << obj;
}

template<typename T>
void TextFile<T>::Close()
{
	this->textWriteStream.close();
	this->textReadStream.close();
}

template<typename T>
bool TextFile<T>::IsEndOfFile()
{
	return this->textReadStream.eof() || this->textWriteStream.eof();
}
