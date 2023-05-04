#pragma once

#include <QWidget>
#include <qpushbutton.h>
#include <qlineedit.h>

#include "Products.h"
#include "ProductTable.h"


class EditMenu : public QWidget
{
	Q_OBJECT
	QWidget* child;     // Виджет меню редактирования
	bool showOnlyNumeric;   // Показыват ьтолько числовые поля

protected:
	char modeFlag;  // Режим работы, подробнее в SetModeFlag()
public: 
	EditMenu(QWidget* parent = nullptr);  // Конструктор

	// Конструктор для редактирования объекта
	EditMenu(QWidget* child, bool showOnlyNumeric = false, QWidget* parent = nullptr);
	// Установить режим работы: 'c' - режим создания, 'e' - режим редактирования 'f' - режим фильтра
	void SetModeFlag(char flag);

	void SetTitle(QString title);   // Установить имя меню

	void SetupProductMenu(Product* obj);	// Настроить меню продукта

	void SetupComputerElementMenu(ComputerElement*);	// Настроить меню компонента компьютера
	void SetupHouseTechMenu(HouseTech* obj);	// Настроить меню домашней техники
	void SetupExternalTechMenu(ExternalTech* obj);	// Настроить меню внешних устройств

	void SetupCPUMenu(CPU* obj);	// Настроить меню процессора
	void SetupGPUMenu(GPU* obj);	// Настроить меню видеокарты

	void SetupFridgeMenu(Fridge* obj);	// Настроить меню холодильника
	void SetupWashMachineMenu(Washmachine* obj);	// Настроить меню стиральной машины

	void SetupMouseMenu(Mouse* obj);	// Настроить меню мышки
	void SetupKeyboardMenu(Keyboard* obj);	// Настроить меню клавиатуры

	// Для всех функций из категории Save... действует одинаковая логика:
	// Считывается строка из соответсвующего TextEdit, и с помощью нужной
	// функции она проверяется на корректность для текущего данного. В случае ошибки генгерируется исключение.
	// В случае работы меню в режиме редактирования фильтра, если строка TextEdit пустая,
	// то такой же пустой она сохраняется в фильтр, без проверки исключений

	bool SaveProductParams(Product* obj);	// Сохранить параметры продукта

	bool SaveComputerElementParams(ComputerElement* obj); // Сохранить параметры компьютера
	bool SaveHouseTechParams(HouseTech* obj); // Сохранить параметры домашней техники
	bool SaveExternalTechParams(ExternalTech* obj); // Сохранить параметры внешних устройств

	bool SaveCPUParams(CPU* obj); // Сохранить параметры процессора
	bool SaveGPUParams(GPU* obj); // Сохранить параметры видеокарты

	bool SaveFridgeParams(Fridge* obj); // Сохранить параметры холодильника
	bool SaveWashMachineParams(Washmachine* obj); // Сохранить параметры стиральной машины

	bool SaveMouseParams(Mouse* obj); // Сохранить параметры мышки
	bool SaveKeyboardParams(Keyboard* obj); // Сохранить параметры клавиатуры

signals:
	void objectEdited(Product* obj, char action);	// Объект был отредактирован
	void updateTables();	// Обновить таблицы с продуктами
};

