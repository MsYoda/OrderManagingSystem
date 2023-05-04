#include "MouseEditMenu.h"
// Конструктор
MouseEditMenu::MouseEditMenu(QWidget* parent) : EditMenu(nullptr, parent)
{
	ui.setupUi(this);
	this->editObj = nullptr;
}
// Нажата кнопка отмены
void MouseEditMenu::CloseMenu()
{
	if (this->modeFlag == 'c')
		if (editObj) delete editObj;
	editObj = nullptr;

	this->deleteLater();
}
// Конструктор с параметрами
MouseEditMenu::MouseEditMenu(Mouse* cpuObj, char mode, QWidget* parent, bool showOnlyNumeric)
	: EditMenu(this, showOnlyNumeric, parent)
{
	this->modeFlag = mode;
	this->editObj = cpuObj;
	ui.setupUi(this);
	ui.frame->setAutoFillBackground(true);
	this->SetupMouseMenu(cpuObj);
	connect(ui.save_button, SIGNAL(clicked()), this, SLOT(SaveButtonClicked()));
	connect(ui.back_button, SIGNAL(clicked()), this, SLOT(CloseMenu()));
}

MouseEditMenu::~MouseEditMenu()
{
	this->CloseMenu();
}

// Кнопка сохранить была нажата
void MouseEditMenu::SaveButtonClicked()
{
	bool result = this->SaveMouseParams(this->editObj);
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
