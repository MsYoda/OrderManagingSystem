#include "ExternalTech.h"

// Генерация описания
QString& ExternalTech::GenerateDescription(QString& str)
{
	dynamic_cast<Product*>(this)->GenerateDescription(str);
	str += "Интерфейс подключения: " + this->connectionInterface + "\n";
	return str;
}

// Конструктор
ExternalTech::ExternalTech()
{
	this->connectionInterface = "";
}

// Установить интерфейс подключения
void ExternalTech::SetConnectionInterface(QString interface) { this->connectionInterface = interface; }

// Вернуть интерфейс подключения
QString ExternalTech::GetConnectionInterface() { return this->connectionInterface; }

// Оператор сравнения
bool ExternalTech::operator==(const ExternalTech& b)
{
	bool result = false;
	result = dynamic_cast<Product&>(*this) == dynamic_cast<Product&>(const_cast<ExternalTech&>(b));

	if (result == true)
	{
		if (this->connectionInterface == b.connectionInterface) result = true;
		else result = false;
	}
	return result;
}

//
// Перегрузки ввода-вывода в файл
//
fstream& operator>>(fstream& in, ExternalTech& obj)
{
	in >> dynamic_cast<Product&>(obj);
	in >> obj.connectionInterface;
	return in;
}

fstream& operator<<(fstream& out, ExternalTech& obj)
{
	out << dynamic_cast<Product&>(obj);
	out << obj.connectionInterface;
	return out;
}
