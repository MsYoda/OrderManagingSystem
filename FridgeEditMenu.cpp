#include "FridgeEditMenu.h"

// Конструктор
FridgeEditMenu::FridgeEditMenu(QWidget* parent) : EditMenu(nullptr, parent)
{
	ui.setupUi(this);
	this->editObj = nullptr;
}
// Нажата кнопка отмены
void FridgeEditMenu::CloseMenu()
{
	if (this->modeFlag == 'c')
		if (editObj) delete editObj;
	editObj = nullptr;

	this->deleteLater();
}

// Конструктор с параметрами
FridgeEditMenu::FridgeEditMenu(Fridge* cpuObj, char mode, QWidget* parent, bool showOnlyNumeric)
	: EditMenu(this, showOnlyNumeric, parent)
{
	this->modeFlag = mode;
	this->editObj = cpuObj;
	ui.setupUi(this);
	ui.frame->setAutoFillBackground(true);
	this->SetupFridgeMenu(cpuObj);
	connect(ui.save_button, SIGNAL(clicked()), this, SLOT(SaveButtonClicked()));
	connect(ui.back_button, SIGNAL(clicked()), this, SLOT(CloseMenu()));
}

FridgeEditMenu::~FridgeEditMenu()
{
	this->CloseMenu();
}

// Кнопка сохранить была нажата
void FridgeEditMenu::SaveButtonClicked()
{
	bool result = this->SaveFridgeParams(this->editObj);
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
