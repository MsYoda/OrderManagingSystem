#include "Review.h"
// Конструктор
Review::Review()
{
	this->mark = 0;
	this->productID = 0;
	this->text = "";
	this->username = "";
}
// Установить ID товара
void Review::SetProductID(int id) { this->productID = id; }
// Установить текст отзыва
void Review::SetText(QString txt) { this->text = txt; }
// Установить оценку
void Review::SetMark(int mark) { this->mark = mark; }
// Установить имя пользователя
void Review::SetUsername(QString name)
{
	this->username = name;
}
// Узнать ID товара
int Review::GetProductID() { return this->productID; }
// Узнать текст отзыва
QString Review::GetText() { return this->text; }
// Узнать оценку
int Review::GetMark() { return this->mark; }
// Узнать имя пользоввателя
QString Review::GetUsername()
{
	return this->username;
}
// Оператор больше
bool Review::operator>(Review& b)
{
	return this->productID > b.productID;
}
// Оператор меньше
bool Review::operator<(Review& b)
{
	return this->productID < b.productID;
}

// Оператор меньше или равно
bool Review::operator<=(Review& b)
{
	return this->productID < b.productID || *this == b;
}
// Оператор больше или равно
bool Review::operator>=(Review& b)
{
	return this->productID > b.productID || *this == b;
}
// Оператор равно
bool Review::operator==(Review& b)
{
	
	if (this->productID == b.productID && this->mark == b.mark && this->text == b.text && this->username == b.username)
		return true;
	else
		return false;
}
// оператор не равно
bool Review::operator!=(Review& b)
{
	return !(*this == b);
}

//
// Операторы ввода/вывода
//
std::fstream& operator>>(std::fstream& in, Review& obj)
{
	in >> obj.text;
	in.read(reinterpret_cast<char*>(&obj.productID), sizeof(int));
	in.read(reinterpret_cast<char*>(&obj.mark), sizeof(int));
	in >> obj.username;
	return in;
}

std::fstream& operator<<(std::fstream& out, Review& obj)
{
	out << obj.text;
	out.write(reinterpret_cast<char*>(&obj.productID), sizeof(int));
	out.write(reinterpret_cast<char*>(&obj.mark), sizeof(int));
	out << obj.username;
	return out;
}
