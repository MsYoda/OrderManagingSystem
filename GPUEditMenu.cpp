#include "GPUEditMenu.h"

// Нажата кнопка отмены
void GPUEditMenu::CloseMenu()
{
	if (this->modeFlag == 'c')
		if (editObj) delete editObj;
	editObj = nullptr;

	this->deleteLater();

	this->deleteLater();
}
// Конструктор
GPUEditMenu::GPUEditMenu(QWidget* parent) : EditMenu(nullptr, parent)
{
	ui.setupUi(this);
	this->editObj = nullptr;
}
// Конструктор с параметрами
GPUEditMenu::GPUEditMenu(GPU* cpuObj, char mode, QWidget* parent, bool showOnlyNumeric)
	: EditMenu(this, showOnlyNumeric, parent)
{
	this->modeFlag = mode;
	this->editObj = cpuObj;
	ui.setupUi(this);
	ui.frame->setAutoFillBackground(true);
	this->SetupGPUMenu(cpuObj);
	connect(ui.save_button, SIGNAL(clicked()), this, SLOT(SaveButtonClicked()));
	connect(ui.back_button, SIGNAL(clicked()), this, SLOT(CloseMenu()));
}

GPUEditMenu::~GPUEditMenu()
{
	this->CloseMenu();
}

// Кнопка сохранить была нажата
void GPUEditMenu::SaveButtonClicked()
{
	bool result = this->SaveGPUParams(this->editObj);
	if (result)
	{
		// Если в режиме фильтра активны оба меню, то сигнал не излчучается
		if (!(this->parentWidget()->findChild<EditMenu*>("left_filter") && this->parentWidget()->findChild<EditMenu*>("right_filter")))
		{
			emit objectEdited(this->editObj, this->modeFlag);
			emit updateTables();
		}
		this->deleteLater();
	}
}

