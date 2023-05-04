#include "User.h"
// Конструктор
User::User()
{
	this->username = "";
	this->password = "";
	this->rating = 3;
}
// Конструктор с данными
User::User(QString username, QString password)
{
	this->username = username;
	this->password = password;
	this->rating = 3;
}
// Установить рейтинг
void User::SetRating(float raiting) { this->rating = raiting; }
// Установить имя пользователя
void User::SetUserName(QString name) { this->username = name; }
// Установить пароль
void User::SetPassword(QString pass) { this->password = pass; }
// Вернуть имя пользователя
QString User::GetUserName() { return this->username; }
// Вернуть пароль
QString User::GetPassword() { return this->password; }
// Вернуть рейтинг
float User::GetRating() { return this->rating; }
// Вернуть функцию сравнения
User::SingInComparator* User::GetComparator() { return &this->comparator; }

// Оператор больше
bool User::operator>(User& b) { return this->rating > b.rating; }
// Оператор меньше
bool User::operator<(User& b) { return this->rating < b.rating; }
// Оператор больше или равно
bool User::operator>=(User& b) { return *this > b || *this == b; }
// Оператор меньше или равно
bool User::operator<=(User& b) { return *this < b || *this == b; }
// Оператор равно
bool User::operator==(User& b) { return this->rating == b.rating && this->username == b.username && this->password == b.password; }
// Оператор не равно
bool User::operator!=(User& b) { return !(*this == b); }

// Проерка является ли объект "пустым"(имеет в себе данные не по умолчанию)
bool User::IsEmpty()
{
	if (this->username.length() == 0 || this->password.length() == 0) return true;
	return false;
} 

// Проверка на соотвествие данных при входе в систему
bool User::SingInComparator::operator()(User* a, User* b)
{
	User result;
	if (b->GetUserName().length() == 0 || b->GetPassword().length() == 0) return false;

	if (a->GetUserName().length() > 0 && a->GetUserName() == b->GetUserName()) result.SetUserName(a->GetUserName());
	if (a->GetPassword().length() > 0 && a->GetPassword() == b->GetPassword()) result.SetPassword(a->GetPassword());
	return result == *b;
}


//
// Операторы ввода/вывода в файл
//
std::fstream& operator>>(std::fstream& in, User& obj)
{
	in >> obj.username;
	in >> obj.password;
	in.read(reinterpret_cast<char*>(&obj.rating), sizeof(float));
	return in;
}

std::fstream& operator<<(std::fstream& out, User& obj)
{
	out << obj.username;
	out << obj.password;
	out.write(reinterpret_cast<char*>(&obj.rating), sizeof(float));
	return out;
}