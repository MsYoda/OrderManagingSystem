#pragma once
#include "Product.h"

class HouseTech :
	public Product
{
protected:
	QString placement;  // Размещение
	QString classOFConsuming;   // Класс энергопотребления

public:
	HouseTech(); // Конструктор

	void SetPlacement(QString type); // Установить тип размещения
	void SetClassOFEnergyConsuming(QString consuming); // Установить класс энергопотребления

	QString GetPlacement();	// Узнать размещение
	QString GetClassOfEnergyConsuming(); // Узнать тип энергопотребления

	bool operator==(const HouseTech& b); // Оператор сравнения

	QString& GenerateDescription(QString& str); // Генерация описания

	// Перегрузки ввода-вывода в файл
	friend fstream& operator>>(fstream& in, HouseTech& obj);
	friend fstream& operator<<(fstream& out, HouseTech& obj);
};

