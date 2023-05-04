#include "ComputerElement.h"

// Генерация описания
QString& ComputerElement::GenerateDescription(QString& str)
{
	dynamic_cast<Product*>(this)->GenerateDescription(str);
	str += "Наличие возможности разгона: ";
	str.append(this->boostMode);
	str += "\nДата выхода: " + QString::number(this->dateOfRelease.day) + "." + QString::number(this->dateOfRelease.month)
		+ "." + QString::number(this->dateOfRelease.year) + "\n";
	return str;
}

// Конструктор
ComputerElement::ComputerElement() : Product()
{
	this->boostMode = ' ';
	this->dateOfRelease = { 0, 0, 0 };
}

// Уставноить режим "разгона"
void ComputerElement::SetBoostMode(char exisist) { this->boostMode = exisist; }

// Установить дату релиза
void ComputerElement::SetDateOfRelease(Date newDate) { this->dateOfRelease = newDate; }

// Узнать о наличии режима разгона
char ComputerElement::GetBoostModeExist() { return this->boostMode; }

// Узнать дату релиза
Date ComputerElement::GetDateOfRelease() { return this->dateOfRelease;  }

// Оператор сравнения
bool ComputerElement::operator==(const ComputerElement& b)
{
	bool result = false;
	result = dynamic_cast<Product&>(*this) == dynamic_cast<Product&>(const_cast<ComputerElement&>(b));

	if (result == true)
	{
		if (this->boostMode == b.boostMode && this->dateOfRelease == b.dateOfRelease) result = true;
		else result = false;
	}
	return result;
}

//
// Перегрузки ввода-вывода в файл
//
fstream& operator>>(fstream& in, ComputerElement& obj)
{
	in >> dynamic_cast<Product&>(obj);
	in.read(reinterpret_cast<char*>(&obj.boostMode), 1);
	in.read(reinterpret_cast<char*>(&obj.dateOfRelease.day), sizeof(int));
	in.read(reinterpret_cast<char*>(&obj.dateOfRelease.month), sizeof(int));
	in.read(reinterpret_cast<char*>(&obj.dateOfRelease.year), sizeof(int));
	return in;
}

fstream& operator<<(fstream& out, ComputerElement& obj)
{
	out << dynamic_cast<Product&>(obj);
	out.write(reinterpret_cast<char*>(&obj.boostMode), 1);
	out.write(reinterpret_cast<char*>(&obj.dateOfRelease.day), sizeof(int));
	out.write(reinterpret_cast<char*>(&obj.dateOfRelease.month), sizeof(int));
	out.write(reinterpret_cast<char*>(&obj.dateOfRelease.year), sizeof(int));
	return out;
}
