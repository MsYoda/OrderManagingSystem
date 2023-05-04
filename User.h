#pragma once
#include <QtCore/qstring.h>
//#include "OrderSystem.h"
#include <fstream>
#include <QString>
#include "ioqstring.h"
#include "templates///Comparator.h"

class User
{
	QString username; // Имя пользователя
	QString password; // Пароль
	float rating; // Рейтинг

	// Проверка на соотвествие данных при входе в систему
	class SingInComparator : public Comparator<User>
	{
		bool operator()(User* a, User* b);
	};
	SingInComparator comparator; // Объект "функции" сравнения

public:
	User(); // Конструктор
	User(QString username, QString password); // Конструктор с данными

	void SetRating(float raiting); // Установить рейтинг

	void SetUserName(QString name); // Установить имя пользователя
	void SetPassword(QString pass); // Установить пароль

	QString GetUserName(); // Вернуть имя пользователя
	QString GetPassword(); // Вернуть пароль
	float GetRating(); // Вернуть рейтинг
	SingInComparator* GetComparator(); // Вернуть функцию сравнения

	// Операторы сравнения
	bool operator>(User& b);
	bool operator<(User& b);
	bool operator>=(User& b);
	bool operator<=(User& b);
	bool operator==(User& b);
	bool operator!=(User& b);

	
	bool IsEmpty(); // Проерка является ли объект "пустым"(имеет в себе данные не по умолчанию)

	// Операторы ввода/вывода в файл
	friend std::fstream& operator>>(std::fstream& in, User& obj);
	friend std::fstream& operator<<(std::fstream& out, User& obj);
};

