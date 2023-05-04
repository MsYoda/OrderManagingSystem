#include "Product.h"
#include <string>

// Оператор сравнения
bool Product::operator==(const Product& b)
{
	if (this->cost == b.cost && this->productID == b.productID && this->name == b.name) return true;
	return false;
}
// Установить цену
void Product::SetCost(const int& cost)
{
	this->cost = cost;
}
// Установить имя
void Product::SetName(const QString& name)
{
	this->name = name;
	this->name = name;
}
// Установить ID
void Product::SetProductID(const int& productID)
{
	this->productID = productID;
}
// Вернуть цену
int Product::GetCost()
{
	return this->cost;
}
// Вернуть имя
QString Product::GetName()
{
	return this->name;
}
// Вернуть ID
int Product::GetID()
{
	return this->productID;
}
QWidget* Product::OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric)
{
	return nullptr;
}
const QString& Product::GetTypeName()
{
	return QString();
}
QString Product::GenerateDescription()
{
	return QString();
};
Product::FilterComparator* Product::GetFilterComparator()
{
	return nullptr;
}
// Сгенерировать описание
QString& Product::GenerateDescription(QString& str)
{
	str += "Название: " + this->name + "\n";
	str += "Цена: " + QString::number(this->cost) + " $\n";
	return str;
}
// Конструктор
Product::Product()
{
	this->cost = 0;
	this->name = "";
	this->productID = 0;
}
//
// Перегрузки ввода-вывода в файл
//
fstream& operator>>(fstream& in, Product& obj)
{
	in >> obj.name;
	in.read(reinterpret_cast<char*>(&obj.cost), sizeof(int));
	in.read(reinterpret_cast<char*>(&obj.productID), sizeof(int));
	return in;
}

fstream& operator<<(fstream& out, Product& obj)
{
	out << obj.name;
	out.write(reinterpret_cast<char*>(&obj.cost), sizeof(int));
	out.write(reinterpret_cast<char*>(&obj.productID), sizeof(int));
	return out;
}

