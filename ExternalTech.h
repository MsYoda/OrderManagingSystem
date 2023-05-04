#pragma once
#include "Product.h"
class ExternalTech :
	public Product
{
protected:
	QString connectionInterface;    // Интерфейс подключения

public:
	ExternalTech(); // Конструктор

	void SetConnectionInterface(QString interface); // Установить интерфейс подключения
	QString GetConnectionInterface();   // Вернуть интерфейс подключения

	bool operator==(const ExternalTech& b); // Оператор сравнения

	QString& GenerateDescription(QString& str); // Генерация описания

	// Перегрузки ввода-вывода в файл
	friend fstream& operator>>(fstream& in, ExternalTech& obj);
	friend fstream& operator<<(fstream& out, ExternalTech& obj);
};

