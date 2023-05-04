#pragma once
#include <string>
#include <QString>
#include <QWidget>
#include <fstream>
#include "templates///Comparator.h"
#include "ioqstring.h"

using namespace std;

class Product
{
protected:
	int cost;	// Цена
	QString name;	// Имя товара
	int productID;	// ID продукта
	class FilterComparator	// Виртуальный функтор для работы фильтра
	{
	public:
		// Функция проверят obj на соотвествие фильтру
		virtual bool operator() (Product* left, Product* obj, Product* right) { return false; };
	};

public:
	Product();	// Конструктор
	bool operator==(const Product& b);	// Оператор сравнения

	void SetCost(const int& cost);	// Установить цену
	void SetName(const QString& name);	// Установить имя
	void SetProductID(const int& productID);	// Установить ID

	int GetCost();	// Вернуть цену
	QString GetName();	// Вернуть имя
	int GetID();	// Вернуть ID

	// Открыть меню редактирования
	virtual QWidget* OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric = false);
	
	// Вернуть имя типа
	virtual const QString& GetTypeName();

	// Функция для использования в производных классах, которая сгенерирует описание
	virtual QString GenerateDescription();

	// Вернуть функтор FilterComparator
	virtual FilterComparator* GetFilterComparator();

	QString& GenerateDescription(QString& str);	// Сгенерировать описание
	
	// Перегрузки ввода-вывода в файл
	friend fstream& operator>>(fstream& in, Product& obj);
	friend fstream& operator<<(fstream& out, Product& obj);

};
