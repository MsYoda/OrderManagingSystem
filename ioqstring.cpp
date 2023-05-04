#include "ioqstring.h"

// Перегрузка вывода QString из бинарного файла
std::fstream& operator>>(std::fstream& in, QString& obj)
{
	int len;
	char* buf;
	// Считывание длины строки
	in.read(reinterpret_cast<char*>(&len), sizeof(int));
	if (!in.eof())
	{
		// Считывание len символов из файла в buf
		buf = new char[len + 1];
		in.read((char*)buf, len);
		buf[len] = '\0';
		obj = buf; // Запись buf в QString
		delete[] buf;
	}
	return in;
}

// Перегрузка записи QString в бинарный файл
std::fstream& operator<<(std::fstream& out, QString& obj)
{
	// Записывается сначала размер строки, а потом сама строка
	std::string str = obj.toStdString();
	int len = str.length();

	out.write(reinterpret_cast<char*>(&len), sizeof(int));
	out.write(str.c_str(), str.size());
	return out;
}