#pragma once

#include <QWidget>
#include "ui_GPUEditMenu.h"
#include "GPU.h"
#include "EditMenu.h"

class GPUEditMenu : public EditMenu
{
	Q_OBJECT
		GPU* editObj;	// объект для изменения

public slots:
	void SaveButtonClicked();	// Кнопка сохранить нажата
	void CloseMenu();	// Кнопка закрыть меню нажата

public:
	GPUEditMenu(QWidget* parent = nullptr);	// Конструктор

	// Конструктор с заданием режима работы
	GPUEditMenu(GPU* cpu, char mode, QWidget* parent, bool showOnlyNumeric = false);
	~GPUEditMenu(); 	// Деструктор


private:
	Ui::GPUEditMenuClass ui;	// доступ к элементам из редактора
};
