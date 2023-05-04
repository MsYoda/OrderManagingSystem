#pragma once

#include "ui_WashMachineEditMenu.h"
#include "WashMachine.h"
#include "EditMenu.h"

class WashMachineEditMenu : public EditMenu
{
	Q_OBJECT
		Washmachine* editObj;	// объект для изменения

public slots:
	void SaveButtonClicked();	// Кнопка сохранить нажата
	void CloseMenu();			// Кнопка закрыть меню нажата
public:
	WashMachineEditMenu(QWidget* parent = nullptr);	// Конструктор

		// Конструктор с заданием режима работы
	WashMachineEditMenu(Washmachine* cpu, char mode, QWidget* parent, bool showOnlyNumeric = false);
	~WashMachineEditMenu();	// Деструктор


private:
	Ui::WashMachineEditMenuClass ui;	// доступ к элементам из редактора
};
