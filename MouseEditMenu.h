#pragma once

#include <QWidget>
#include "ui_MouseEditMenu.h"
#include "Mouse.h"
#include "EditMenu.h"

class MouseEditMenu : public EditMenu
{
	Q_OBJECT
		Mouse* editObj;	// объект для изменения

public slots:
	void SaveButtonClicked();	// Кнопка сохранить нажата
	void CloseMenu();			// Кнопка закрыть меню нажата

public:
	MouseEditMenu(QWidget* parent = nullptr);		// Конструктор

	// Конструктор с заданием режима работы
	MouseEditMenu(Mouse* cpu, char mode, QWidget* parent, bool showOnlyNumeric = false);
	~MouseEditMenu();	// Деструктор


private:
	Ui::MouseEditMenuClass ui;	// доступ к элементам из редактора
};