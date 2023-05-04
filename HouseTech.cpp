#include "HouseTech.h"

// Генерация описания
QString& HouseTech::GenerateDescription(QString& str)
{
	dynamic_cast<Product*>(this)->GenerateDescription(str);
	str += "Класс энергопотребления: " + this->classOFConsuming + "\n";
	str += "Размещение: " + this->placement + "\n";
	return str;
}

// Конструктор
HouseTech::HouseTech()
{
	this->classOFConsuming = this->placement = "";
}

// Установить тип размещения
void HouseTech::SetPlacement(QString type) { this->placement = type; }
// Установить класс энергопотребления
void HouseTech::SetClassOFEnergyConsuming(QString consuming) { this->classOFConsuming = consuming; }
// Узнать размещение
QString HouseTech::GetPlacement() { return this->placement; }
// Узнать тип энергопотребления
QString HouseTech::GetClassOfEnergyConsuming() { return this->classOFConsuming; }

// Оператор сравнения
bool HouseTech::operator==(const HouseTech& b)
{
	bool result = false;
	result = dynamic_cast<Product&>(*this) == dynamic_cast<Product&>(const_cast<HouseTech&>(b));

	if (result == true)
	{
		if (this->classOFConsuming == b.classOFConsuming && this->placement == b.placement) result = true;
		else result = false;
	}
	return result;
}

//
// Перегрузки ввода-вывода в файл
//
fstream& operator>>(fstream& in, HouseTech& obj)
{
	in >> dynamic_cast<Product&>(obj);
	in >> obj.classOFConsuming;
	in >> obj.placement;
	return in;
}

fstream& operator<<(fstream& out, HouseTech& obj)
{
	out << dynamic_cast<Product&>(obj);
	out << obj.classOFConsuming;
	out << obj.placement;
	return out;
}
