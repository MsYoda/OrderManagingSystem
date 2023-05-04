#include "KeyboardEditMenu.h"

// Конструктор
KeyboardEditMenu::KeyboardEditMenu(QWidget* parent) : EditMenu(nullptr, parent)
{
	ui.setupUi(this);
	this->editObj = nullptr;
}
// Нажата кнопка отмены
void KeyboardEditMenu::CloseMenu()
{
	if (this->modeFlag == 'c')
		if (editObj) delete editObj;
	editObj = nullptr;

	this->deleteLater();
}
// Конструктор с параметрами
KeyboardEditMenu::KeyboardEditMenu(Keyboard* cpuObj, char mode, QWidget* parent, bool showOnlyNumeric)
	: EditMenu(this, showOnlyNumeric, parent)
{
	this->modeFlag = mode;
	this->editObj = cpuObj;
	ui.setupUi(this);
	ui.frame->setAutoFillBackground(true);
	this->SetupKeyboardMenu(cpuObj);
	connect(ui.save_button, SIGNAL(clicked()), this, SLOT(SaveButtonClicked()));
	connect(ui.back_button, SIGNAL(clicked()), this, SLOT(CloseMenu()));
}

KeyboardEditMenu::~KeyboardEditMenu()
{
	this->CloseMenu();
}

// Кнопка сохранить была нажата
void KeyboardEditMenu::SaveButtonClicked()
{
	bool result = this->SaveKeyboardParams(this->editObj);
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

