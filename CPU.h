#pragma once
#include "ComputerElement.h"
class CPU :
	public ComputerElement
{
	float speed;    // частота процессора
	int countOfCores;   // число ядер
	const static QString TYPENAME;  // Имя типа - "Процессор"
	QString& GenerateDescription(QString& str); // Сгенерировать описание

	// Функтор для работы фильтра
	class CPUFilterComparator : public FilterComparator
	{
	public:
		// Функция проверят obj на соотвествие фильтру
		bool operator() (Product* left, Product* obj, Product* right) override;
	};
	CPUFilterComparator comparator; // Объект фильтра
public:
	CPU();  // Конструктор
	void SetSpeed(float speed); // Установить частоту
	void SetCountOfCores(int count);    // Установить количество ядер

	float GetSpeed();   // узнать частоту
	int GetCountOfCores();  // Узнать количество ядер

	// Открыть меню редактирования
	QWidget* OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric) override;
	const QString& GetTypeName() override; // Вернуть имя типа

	// Вернуть функтор FilterComparator
	FilterComparator* GetFilterComparator() override;

	QString GenerateDescription() override; // Сгенерировать полное описание

	bool operator==(CPU& b); // Оператор сравнения

	// Перегрузки ввода-вывода в файл
	friend fstream& operator>>(fstream& in, CPU& obj);
	friend fstream& operator<<(fstream& out, CPU& obj);
};

