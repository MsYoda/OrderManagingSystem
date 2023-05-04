#pragma once
#include "ExternalTech.h"

class Mouse :
	public ExternalTech
{
	QString typeOfWheel;	// Тип колёсика
	int countOfButtons;	// Количество кнопок
	const static QString TYPENAME; // Имя типа - "Мышка"

	// Функтор для работы фильтра
	class MouseFilterComparator : public FilterComparator
	{
	public:
		// Функция проверят obj на соотвествие фильтру
		bool operator() (Product* left, Product* obj, Product* right) override;
	};
	MouseFilterComparator comparator; // Объект фильтра

	QString& GenerateDescription(QString& str); // Сгенерировать описание

public:
	Mouse(); // Конструктор

	void SetTypeOfWheel(QString type); // Установить тип колёсика
	void SetCountOfButtons(int count); // Установить количетство кнопок

	QString GetTypeOfWheel(); // Узнать тип колёсика
	int GetCountOFButtons();	// Узнать количество кнопок

	// Открыть меню редактирования
	QWidget* OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric = false) override;
	const QString& GetTypeName() override; // Вернуть имя типа

	QString GenerateDescription() override; // Сгенерировать полное описание
	// Вернуть функтор FilterComparator
	FilterComparator* GetFilterComparator() override;

	bool operator==(Mouse& b); // Оператор сравнения

	// Перегрузки ввода-вывода в файл
	friend fstream& operator>>(fstream& in, Mouse& obj);
	friend fstream& operator<<(fstream& out, Mouse& obj);
};

