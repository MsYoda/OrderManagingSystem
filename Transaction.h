#pragma once
#include <QString>
#include <fstream>
#include "ioqstring.h"

using namespace std;

struct Transaction // Информация о переводе
{
	QString sender; // Имя пользовател отправителя
	QString receiver; // Имя пользовател получателя
	int sum; // Сумма

	Transaction(); // Конструктор
	Transaction(QString sender, QString receiver, int sum); // Конструктор

	// Операторы ввода/вывода в файл
	friend fstream& operator<<(fstream& out, Transaction& obj);
	friend fstream& operator>>(fstream& in, Transaction& obj);
};

