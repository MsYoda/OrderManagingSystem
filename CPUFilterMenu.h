#pragma once

#include <QWidget>
#include "ui_CPUFilterMenu.h"
#include "FilterMenu.h"

class CPUFilterMenu : public FilterMenu
{
	Q_OBJECT

public:
	CPUFilterMenu(QWidget *parent = nullptr);
	~CPUFilterMenu();

private:
	Ui::CPUFilterMenuClass ui;
};
