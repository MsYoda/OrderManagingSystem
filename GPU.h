#pragma once
#include "ComputerElement.h"

class GPU :
	public ComputerElement
{
	int videoMemory;    // Количество видеопамяти
	QString typeOfMemory; // Тип памяти
	const static QString TYPENAME;  // Имя типа - "Видеокарта"

	// Функтор для работы фильтра
	class GPUFilterComparator : public FilterComparator
	{
	public:
		// Функция проверят obj на соотвествие фильтру
		bool operator() (Product* left, Product* obj, Product* right) override;
	};
	GPUFilterComparator comparator; // Объект фильтра

	QString& GenerateDescription(QString& str); // Сгенерировать описание
public:
	GPU(); // Конструктор

	void SetVideoMemory(int amount); // Установить объём видеопамяти
	void SetTypeOfMemory(QString type); // Установить тип памяти

	int GetVideoMemory();   // Узнать количество видеопамяти
	QString GetTypeOfMemory();  // Узнать тип памяти
		
	// Открыть меню редактирования
	QWidget* OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric = false) override;
	const QString& GetTypeName() override; // Вернуть имя типа

	QString GenerateDescription() override; // Сгенерировать полное описание
	// Вернуть функтор FilterComparator
	FilterComparator* GetFilterComparator() override;

	bool operator==(GPU& b); // Оператор сравнения

	// Перегрузки ввода-вывода в файл
	friend fstream& operator>>(fstream& in, GPU& obj);
	friend fstream& operator<<(fstream& out, GPU& obj);

};

