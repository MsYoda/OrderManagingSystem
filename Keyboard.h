#pragma once
#include "ExternalTech.h"

class Keyboard :
	public ExternalTech
{
	char numbadExistence; // Сущестовавание нумпада
	QString typeOfKeyboard;	// Тип клавиатуры
	const static QString TYPENAME; // Имя типа - "Клавиатура"

	// Функтор для работы фильтра
	class KeyboardFilterComparator : public FilterComparator
	{
	public:
		// Функция проверят obj на соотвествие фильтру
		bool operator() (Product* left, Product* obj, Product* right) override;
	};
	KeyboardFilterComparator comparator; // Объект фильтра

	QString& GenerateDescription(QString& str); // Сгенерировать описание

public:
	Keyboard(); // Конструктор

	void SetNumpadExistense(char exist); // Установить существование нумпада
	void SetTypeOfKeyboard(QString type);	// Установить тип клавиатуры

	char GetNumpadExistense(); // Узнать существование нумпада
	QString GetTypeOfKeyboard(); // Узнать тип клавитуры

	// Открыть меню редактирования
	QWidget* OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric = false) override;
	const QString& GetTypeName() override; // Вернуть имя типа

	QString GenerateDescription() override; // Сгенерировать полное описание
	// Вернуть функтор FilterComparator
	FilterComparator* GetFilterComparator() override; 

	bool operator==(Keyboard& b); // Оператор сравнения

	// Перегрузки ввода-вывода в файл
	friend fstream& operator>>(fstream& in, Keyboard& obj);
	friend fstream& operator<<(fstream& out, Keyboard& obj);
};

