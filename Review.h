#pragma once
#include <QtCore/qstring.h>
#include "User.h"
#include <fstream>
#include "ioqstring.h"

class Review
{
	int productID; // ID товара
	QString text; // Текст отзыва
	int mark; // Оценка
	QString username; // Имя пользователя

public:
	Review(); // Конструктор

	void SetProductID(int id); // Установить ID товара
	void SetText(QString txt); // Установить текст отзыва
	void SetMark(int mark); // Установить оценку
	void SetUsername(QString name); // Установить имя пользователя

	int GetProductID(); // Узнать ID товара
	QString GetText(); // Узнать текст отзыва
	int GetMark();	// Узнать оценку
	QString GetUsername(); // Узнать имя пользоввателя

	// Опеарторы сравнения
	bool operator>(Review& b);
	bool operator<(Review& b);
	bool operator>=(Review& b);
	bool operator<=(Review& b);
	bool operator==(Review& b);
	bool operator!=(Review& b);

	// Операторы ввода/вывода
	friend std::fstream& operator>>(std::fstream& in, Review& obj);
	friend std::fstream& operator<<(std::fstream& out, Review& obj);
};

