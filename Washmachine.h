#pragma once
#include "HouseTech.h"

class Washmachine :
	public HouseTech
{
	float maxWeight; // Максимальная загрузка
	int countOfPrograms; // Количество программ
	const static QString TYPENAME; // Имя типа - "Стиральная машина"

	// Функтор для работы фильтра
	class WashMacineFilterComparator : public FilterComparator
	{
	public:
		// Функция проверят obj на соотвествие фильтру
		bool operator() (Product* left, Product* obj, Product* right) override;
	};

	WashMacineFilterComparator comparator; // Объект фильтра
	QString& GenerateDescription(QString& str); // Сгенерировать описание

public:
	Washmachine();  // Конструктор

	void SetMaxWeight(float num); // Установить максимальную загрузку
	void SetCountOfPrograms(int count); // Установить число программ

	float GetMaxWeight();	// Узнать максимальную загрузку
	int GetCountOfPrograms(); // Установить число программ

	// Открыть меню редактирования
	QWidget* OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric = false) override;
	const QString& GetTypeName() override; // Вернуть имя типа

	QString GenerateDescription() override; // Сгенерировать полное описание
	// Вернуть функтор FilterComparator
	FilterComparator* GetFilterComparator() override;

	bool operator==(Washmachine& b); // Оператор сравнения

	// Перегрузки ввода-вывода в файл
	friend fstream& operator>>(fstream& in, Washmachine& obj);
	friend fstream& operator<<(fstream& out, Washmachine& obj);
};

