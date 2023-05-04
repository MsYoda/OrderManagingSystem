#pragma once
#include "BaseTable.h"
#include "Bank.h"
#include "qlabel.h"
#include <QWidget>


class BankTable :
	public BaseTable
{
	Q_OBJECT
	Bank* bank; // Указатель на банк
public:
	BankTable(QWidget* parent = nullptr);   // Конструктор
	void SetupTable(Bank* bank);    // Установить поля таблицы
	void UpdateTable(); // Обновить таблицу
};

