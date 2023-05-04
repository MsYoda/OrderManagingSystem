#pragma once

#include <QWidget>
#include "ui_FridgeFilterMenu.h"
#include "FilterMenu.h"

class FridgeFilterMenu : public FilterMenu
{
	Q_OBJECT

public:
	FridgeFilterMenu(QWidget *parent = nullptr);
	~FridgeFilterMenu();

private:
	Ui::FridgeFilterMenuClass ui;
};
