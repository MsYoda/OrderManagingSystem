#pragma once
#include <QWidget>
#include "ui_CPUEditMenu.h"
#include "CPU.h"
#include "EditMenu.h"

class CPUEditMenu : public EditMenu
{
	Q_OBJECT
	CPU* editObj;	// объект для изменения

public slots:
	void SaveButtonClicked();	// Кнопка сохранить нажата
	void CloseMenu();			// Кнопка закрыть меню нажата

public:
	CPUEditMenu(QWidget* parent = nullptr);	// Конструктор

	// Конструктор с заданием режима работы
	CPUEditMenu(CPU* cpu, char mode, QWidget* parent, bool showOnlyNumeric = false);
	~CPUEditMenu();	// Деструктор


private:
	Ui::CPUEditMenuClass ui;	// доступ к элементам из редактора
};
