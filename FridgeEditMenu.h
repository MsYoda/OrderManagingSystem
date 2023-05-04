#pragma once

#include <QWidget>
#include "ui_FridgeEditMenu.h"
#include "Fridge.h"
#include "EditMenu.h"

class FridgeEditMenu : public EditMenu
{
	Q_OBJECT
		Fridge* editObj; // объект для изменения

public slots:
	void SaveButtonClicked();	// Кнопка сохранить нажата
	void CloseMenu();	// Кнопка закрыть меню нажата

public:
	FridgeEditMenu(QWidget* parent = nullptr);	// Конструктор

	// Конструктор с заданием режима работы
	FridgeEditMenu(Fridge* obj, char mode, QWidget* parent, bool showOnlyNumeric = false);
	~FridgeEditMenu(); // Деструктор


private:
	Ui::FridgeEditMenuClass ui; // доступ к элементам из редактора
};
