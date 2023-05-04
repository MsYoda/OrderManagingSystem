#pragma once

#include <QWidget>
#include "ui_WashmachineFilterMenu.h"
#include "FilterMenu.h"

class WashmachineFilterMenu : public FilterMenu
{
	Q_OBJECT

public:
	WashmachineFilterMenu(QWidget *parent = nullptr);
	~WashmachineFilterMenu();

private:
	Ui::WashmachineFilterMenuClass ui;
};
