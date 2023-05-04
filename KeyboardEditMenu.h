#pragma once

#include <QWidget>
#include "ui_KeyboardEditMenu.h"
//#include "Keyboard.h"
#include "EditMenu.h"

class KeyboardEditMenu : public EditMenu
{
	Q_OBJECT
		Keyboard* editObj;	// объект для изменения

public slots:
	void SaveButtonClicked();	// Кнопка сохранить нажата
	void CloseMenu();	// Кнопка закрыть меню нажата

public:
	KeyboardEditMenu(QWidget* parent = nullptr);	// Конструктор

	// Конструктор с заданием режима работы
	KeyboardEditMenu(Keyboard* cpu, char mode, QWidget* parent, bool showOnlyNumeric = false);
	~KeyboardEditMenu(); // Деструктор


private:
	Ui::KeyboardEditMenuClass ui;	// доступ к элементам из редактора
};
