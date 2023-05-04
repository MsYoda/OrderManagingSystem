#pragma once

#include <QWidget>
#include "ui_KeyboardFilterMenu.h"
#include "FilterMenu.h"

class KeyboardFilterMenu : public FilterMenu
{
	Q_OBJECT

public:
	KeyboardFilterMenu(QWidget *parent = nullptr);
	~KeyboardFilterMenu();

private:
	Ui::KeyboardFilterMenuClass ui;
};
