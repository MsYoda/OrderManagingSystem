#pragma once

#include <QWidget>
#include "ui_GPUFilterMenu.h"
#include "FilterMenu.h"

class GPUFilterMenu : public FilterMenu
{
	Q_OBJECT

public:
	GPUFilterMenu(QWidget *parent = nullptr);
	~GPUFilterMenu();

private:
	Ui::GPUFilterMenuClass ui;
};
