#pragma once

#include <QWidget>
#include "ui_MouseFilterMenu.h"
#include "FilterMenu.h"

class MouseFilterMenu : public FilterMenu
{
	Q_OBJECT

public:
	MouseFilterMenu(QWidget *parent = nullptr);
	~MouseFilterMenu();

private:
	Ui::MouseFilterMenuClass ui;
};
