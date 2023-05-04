#pragma once
#include "BinaryFile.h"
#include "FileException.h"
#include <qmessagebox>

// Конструктор
template<typename T>
BinaryFile<T>::BinaryFile(QString filename)
{
	this->fileName = filename;
}

// Установить имя файла
template<typename T>
void BinaryFile<T>::SetFileName(QString fname)
{
	this->fileName = fname;
}

// Открыть файл для чтения
template<typename T>
void BinaryFile<T>::OpenForReading()
{
	try
	{
		this->binaryIOStream.open(this->fileName.toStdString(), std::ios::binary | std::ios::in);
		if (!this->binaryIOStream.is_open()) throw FileException("Файл не открыт! Попытка создать файл!");
	}
	catch (FileException excep) // Если файл не открылся, то попытка его создать
	{
		try
		{
			this->OpenForWriting();
		}
		catch (FileException excep)
		{
			QMessageBox* errorBox = new QMessageBox;
			errorBox->setText(excep.GetMessage());
			errorBox->exec();
		}
		this->Close();
		this->OpenForReading();
	}
}

// Открыть файл для записи
template<typename T>
void BinaryFile<T>::OpenForWriting()
{
	try
	{
		this->binaryIOStream.open(this->fileName.toStdString(), std::ios::binary | std::ios::out);
		if (!this->binaryIOStream.is_open()) throw FileException("\nНевозможно открыть файл " + this->fileName + " для записи или создать его!\n");
	}
	catch (FileException excep)
	{
		QMessageBox* errorBox = new QMessageBox;
		errorBox->setText("Информация не будет сохранена!\n" + excep.GetMessage());
		errorBox->exec();
		return;
	}
	

}

// Прочитать объект
template<typename T>
T BinaryFile<T>::ReadObj()
{
	T obj;
	this->binaryIOStream >> obj;
	return obj;
}

// Записать объект
template<typename T>
void BinaryFile<T>::WriteObj(T* obj)
{
	this->binaryIOStream << *(obj) ;
}

// Закрыть файл
template<typename T>
void BinaryFile<T>::Close()
{
	this->binaryIOStream.close();
}

// Проверка на конец файла
template<typename T>
bool BinaryFile<T>::IsEndOfFile()
{
	if (this->binaryIOStream.eof()) return true;
	else return false;
}

template<typename T>
bool BinaryFile<T>::IsOpen()
{
	return this->binaryIOStream.is_open();
}
