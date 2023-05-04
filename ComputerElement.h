#pragma once
#include "Product.h"
#include "Date.h"

class ComputerElement :
	public Product
{
protected:
	char boostMode; // Режим разгона
	Date dateOfRelease; // Дата выхлда на рынок

public:
	ComputerElement();  // Конструктор

	void SetBoostMode(char exisist);    // Уставноить режим "разгона"
	void SetDateOfRelease(Date newDate);    // Установить дату релиза

	char GetBoostModeExist();   // Узнать о наличии режима разгона
	Date GetDateOfRelease();    // Узнать дату релиза

	bool operator==(const ComputerElement& b);  // Оператор сравнения

	QString& GenerateDescription(QString& str); // Генерация описания

	// Перегрузки ввода-вывода в файл
	friend fstream& operator>>(fstream& in, ComputerElement& obj);
	friend fstream& operator<<(fstream& out, ComputerElement& obj);
};

