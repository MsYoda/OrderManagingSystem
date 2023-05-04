#include "EditMenu.h"
#include "InputExeption.h"
#include "CheckFunctions.h"
#include "ProductTable.h"

// Конструктор
EditMenu::EditMenu(QWidget* parent) : QWidget(parent)
{
	this->child = nullptr;
	this->modeFlag = 'c';
	this->showOnlyNumeric = false;
}

// Конструктор для редактирования объекта
EditMenu::EditMenu(QWidget* child, bool showOnlyNumeric, QWidget* parent) : QWidget(parent)
{
	this->showOnlyNumeric = showOnlyNumeric;
	this->child = child;
	this->modeFlag = 'c';
	QWidget* test1 = parent;
	QMainWindow* test = dynamic_cast<QMainWindow*>(parent);
	// Сигналы об обновлении таблиц
	connect(this, &EditMenu::updateTables, child->parent()->findChild<BaseProductTable*>("admin_product_table"), &BaseProductTable::UpdateTable);
	connect(this, &EditMenu::updateTables, child->parent()->findChild<BaseProductTable*>("user_product_table"), &BaseProductTable::UpdateTable);
	
	// Сигнал, о сохранении действия, сделанного в этом меню в стек отмены действий
	connect(this, &EditMenu::objectEdited, parent->findChild<ProductTable*>("admin_product_table"), &ProductTable::RememberAction);
}

// Установить режим работы: 'c' - режим создания, 'e' - режим редактирования 'f' - режим фильтра
void EditMenu::SetModeFlag(char flag)
{
	this->modeFlag = flag;
}

// Установить имя меню
void EditMenu::SetTitle(QString title)
{
	this->child->findChild<QLabel*>("title")->setText(title);
}

// Настроить меню продукта
void EditMenu::SetupProductMenu(Product* obj)
{
	if (obj->GetCost() != 0)
		this->child->findChild<QLineEdit*>("cost_input")->setText(QString::number(obj->GetCost()));

	if (showOnlyNumeric)
	{
		this->child->findChild<QLineEdit*>("name_input")->hide();
		this->child->findChild<QLabel*>("name")->hide();
	}
	else
		if (obj->GetName().length() != 0)
			this->child->findChild<QLineEdit*>("name_input")->setText(obj->GetName());
}
// Настроить меню компонента компьютера
void EditMenu::SetupComputerElementMenu(ComputerElement* obj)
{
	this->SetupProductMenu(obj);
	QString converter;
	converter.append(obj->GetBoostModeExist());

	if (showOnlyNumeric)
	{
		this->child->findChild<QLineEdit*>("boost_input")->hide();
		this->child->findChild<QLabel*>("boost")->hide();
	}
	else
		if (obj->GetBoostModeExist() != ' ')
			this->child->findChild<QLineEdit*>("boost_input")->setText(converter);

	Date nullDate(0, 0, 0);
	if (obj->GetDateOfRelease() != nullDate)
	{
		converter = QString::number(obj->GetDateOfRelease().day) + "." + QString::number(obj->GetDateOfRelease().month) + "."
			+ QString::number(obj->GetDateOfRelease().year);
		this->child->findChild<QLineEdit*>("release_year_input")->setText(converter);
	}
}

// Настроить меню домашней техники
void EditMenu::SetupHouseTechMenu(HouseTech* obj)
{
	this->SetupProductMenu(obj);
	if (!showOnlyNumeric)
	{
		if (obj->GetPlacement().length() != 0)
			this->child->findChild<QLineEdit*>("placement_input")->setText(obj->GetPlacement());
		if (obj->GetClassOfEnergyConsuming().length() != 0)
			this->child->findChild<QLineEdit*>("consuming_input")->setText(obj->GetClassOfEnergyConsuming());
	}
	else
	{
		this->child->findChild<QLineEdit*>("placement_input")->hide();
		this->child->findChild<QLineEdit*>("consuming_input")->hide();
		this->child->findChild<QLabel*>("placement")->hide();
		this->child->findChild<QLabel*>("consuming")->hide();
	}
}

// Настроить меню внешних устройств
void EditMenu::SetupExternalTechMenu(ExternalTech* obj)
{
	this->SetupProductMenu(obj);
	if (showOnlyNumeric)
	{
		this->child->findChild<QLineEdit*>("interface_input")->hide();
		this->child->findChild<QLabel*>("connection")->hide();
	}
	else
		if (obj->GetConnectionInterface().length() != 0)
			this->child->findChild<QLineEdit*>("interface_input")->setText(obj->GetConnectionInterface());
}

// Настроить меню холодильника
void EditMenu::SetupFridgeMenu(Fridge* obj)
{
	if (this->modeFlag == 'c') return;
	this->SetupHouseTechMenu(obj);
	if (obj->GetCameraVolume() != 0)
		this->child->findChild<QLineEdit*>("volume_input")->setText(QString::number(obj->GetCameraVolume()));
	if (obj->GetNoiseLevel() != 0)
		this->child->findChild<QLineEdit*>("noise_input")->setText(QString::number(obj->GetNoiseLevel()));
}
// Настроить меню стиральной машины
void EditMenu::SetupWashMachineMenu(Washmachine* obj)
{
	if (this->modeFlag == 'c') return;
	this->SetupHouseTechMenu(obj);
	if (obj->GetMaxWeight() != 0)
		this->child->findChild<QLineEdit*>("maxweight_input")->setText(QString::number(obj->GetMaxWeight()));
	if (obj->GetCountOfPrograms() != 0)
		this->child->findChild<QLineEdit*>("programs_input")->setText(QString::number(obj->GetCountOfPrograms()));
}

// Настроить меню мышки
void EditMenu::SetupMouseMenu(Mouse* obj)
{
	if (this->modeFlag == 'c') return;
	this->SetupExternalTechMenu(obj);

	if (showOnlyNumeric)
	{
		this->child->findChild<QLineEdit*>("wheel_input")->hide();
		this->child->findChild<QLabel*>("wheel")->hide();
	}
	else
		if (obj->GetTypeOfWheel().length() != 0)
			this->child->findChild<QLineEdit*>("wheel_input")->setText(obj->GetTypeOfWheel());

	if (obj->GetCountOFButtons() != 0)
		this->child->findChild<QLineEdit*>("keys_input")->setText(QString::number(obj->GetCountOFButtons()));
}
// Настроить меню клавиатуры
void EditMenu::SetupKeyboardMenu(Keyboard* obj)
{
	if (this->modeFlag == 'c') return;
	this->SetupExternalTechMenu(obj);
	QString converter;
	converter.append(obj->GetNumpadExistense());
	if (!showOnlyNumeric)
	{
		if (!(obj->GetNumpadExistense() == ' '))
			this->child->findChild<QLineEdit*>("numpad_input")->setText(converter);
		if (obj->GetTypeOfKeyboard().length() != 0)
			this->child->findChild<QLineEdit*>("keyboardtype_input")->setText(obj->GetTypeOfKeyboard());
	}
	else
	{
		this->child->findChild<QLineEdit*>("numpad_input")->hide();
		this->child->findChild<QLineEdit*>("keyboardtype_input")->hide();
		this->child->findChild<QLabel*>("numpad")->hide();
		this->child->findChild<QLabel*>("keyboard")->hide();
	}
}

// Настроить меню процессора
void EditMenu::SetupCPUMenu(CPU* obj)
{
	if (this->modeFlag == 'c') return;
	this->SetupComputerElementMenu(obj);
	if (obj->GetCountOfCores() != 0)
		this->child->findChild<QLineEdit*>("cores_input")->setText(QString::number(obj->GetCountOfCores()));

	if (obj->GetSpeed() != 0)
		this->child->findChild<QLineEdit*>("speed_input")->setText(QString::number(obj->GetSpeed()));
}

// Настроить меню видеокарты
void EditMenu::SetupGPUMenu(GPU* obj)
{
	if (this->modeFlag == 'c') return;
	this->SetupComputerElementMenu(obj);

	if (obj->GetVideoMemory() != 0)
		this->child->findChild<QLineEdit*>("videomemory_input")->setText(QString::number(obj->GetVideoMemory()));

	if (showOnlyNumeric)
	{
		this->child->findChild<QLabel*>("memory_type")->hide();
		this->child->findChild<QLineEdit*>("memorytype_input")->hide();
	}
	else
		if (obj->GetTypeOfMemory().length() != 0)
			this->child->findChild<QLineEdit*>("memorytype_input")->setText(obj->GetTypeOfMemory());
}

//==================================================
// За дополнительный информацией о происходящем внутри следующих функций
// смотрите EditMenu.h
// =================================================

// Сохранить параметры продукта
bool EditMenu::SaveProductParams(Product* obj)
{
	int iNum = 0;
	QString str;
	if (!(this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("name_input")->text().length() == 0))
	{
		try
		{
			str = this->child->findChild<QLineEdit*>("name_input")->text();
			CheckEngString(&str);
		}
		catch (InputExeption excep)
		{
			QString whereStr = "При вводе названия товара ";
			excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
			return false;
		}
	}
	obj->SetName(this->child->findChild<QLineEdit*>("name_input")->text());

	if (this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("cost_input")->text().length() == 0)
		iNum = 0;
	else
	{
		try
		{
			str = this->child->findChild<QLineEdit*>("cost_input")->text();
			iNum = ConvertToInt(str, 1, 5000);
		}
		catch (InputExeption excep)
		{
			QString whereStr = "При вводе цены ";
			excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
			return false;
		}
	}
	obj->SetCost(iNum);
	return true;
}

// Сохранить параметры домашней техники
bool EditMenu::SaveHouseTechParams(HouseTech* obj)
{
	if (this->SaveProductParams(obj))
	{
		QString buf;
		if (!(this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("placement_input")->text().length() == 0))
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("placement_input")->text();
				CheckRussianLetters(&buf);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе исполнения ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetPlacement(buf);

		if (!(this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("consuming_input")->text().length() == 0))
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("consuming_input")->text();
				CheckEngString(&buf);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе класса энергопотребления ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetClassOFEnergyConsuming(buf);
		return true;
	}
	return false;
}

// Сохранить параметры внешних устройств
bool EditMenu::SaveExternalTechParams(ExternalTech* obj)
{
	if (this->SaveProductParams(obj))
	{
		QString buf;

		if (!(this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("interface_input")->text().length() == 0))
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("interface_input")->text();
				CheckEngString(&buf);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе интерфейса подключения ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetConnectionInterface(buf);
		return true;
	}
	return false;
}

// Сохранить параметры компьютера
bool EditMenu::SaveComputerElementParams(ComputerElement* obj)
{
	QString buf;
	if (this->SaveProductParams(obj))
	{
		if ((this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("boost_input")->text().length() == 0))
			this->child->findChild<QLineEdit*>("boost_input")->setText(QChar(' '));
		else
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("boost_input")->text();
				CheckExistence(&buf);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе наличия возможности разгона ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetBoostMode(this->child->findChild<QLineEdit*>("boost_input")->text().toStdString()[0]);

		Date date = { 0, 0, 0 };
		if (!(this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("release_year_input")->text().length() == 0))
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("release_year_input")->text();
				date = ConvertToDate(&buf);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе даты ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetDateOfRelease(date);

		return true;
	}
	return false;
}

// Сохранить параметры процессора
bool EditMenu::SaveCPUParams(CPU* obj)
{
	QString buf;
	if (this->SaveComputerElementParams(obj))
	{
		int iNum = 0;
		float fNum = 0;

		if (this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("cores_input")->text().length() == 0)
			iNum = 0;
		else
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("cores_input")->text();
				iNum = ConvertToInt(buf, 1, 30);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При числа ядер ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetCountOfCores(iNum);

		if (this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("speed_input")->text().length() == 0)
			fNum = 0;
		else
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("speed_input")->text();
				fNum = ConvertToFloat(buf, 1, 6);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе скорости процессора ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetSpeed(fNum);

		if (modeFlag == 'c')
			obj->SetProductID(Assortment::GetNewID());

		return true;
	}
	return false;
}

// Сохранить параметры видеокарты
bool EditMenu::SaveGPUParams(GPU* obj)
{
	if (this->SaveComputerElementParams(obj))
	{
		QString buf;
		int iNum;
		if (this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("videomemory_input")->text().length() == 0)
			iNum = 0;
		else
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("videomemory_input")->text();
				iNum = ConvertToInt(buf, 1, 20);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе видеопамяти ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetVideoMemory(iNum);
		if (!(this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("memorytype_input")->text().length() == 0))
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("memorytype_input")->text();
				CheckEngString(&buf);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе типа видеопамяти ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetTypeOfMemory(buf);

		if (modeFlag == 'c')
			obj->SetProductID(Assortment::GetNewID());

		return true;
	}
	return false;
}

// Сохранить параметры холодильника
bool EditMenu::SaveFridgeParams(Fridge* obj)
{
	if (this->SaveHouseTechParams(obj))
	{
		QString buf;
		float fNum;
		if (this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("volume_input")->text().length() == 0)
			fNum = 0;
		else
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("volume_input")->text();
				fNum = ConvertToFloat(buf, 1, 100);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе объёма камеры ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetCameraVolume(fNum);
		if (this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("noise_input")->text().length() == 0)
			fNum = 0;
		else
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("noise_input")->text();
				fNum = ConvertToFloat(buf, 1, 100);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе уровня шума ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetNoiseLevel(fNum);

		if (modeFlag == 'c')
			obj->SetProductID(Assortment::GetNewID());
		return true;
	}
	return false;
}

// Сохранить параметры стиральной машины
bool EditMenu::SaveWashMachineParams(Washmachine* obj)
{
	if (this->SaveHouseTechParams(obj))
	{
		QString buf;
		float fNum; int iNum;
		if (this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("maxweight_input")->text().length() == 0)
			fNum = 0;
		else
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("maxweight_input")->text();
				fNum = ConvertToFloat(buf, 1, 50);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе максимальной загрузки ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetMaxWeight(fNum);
		if (this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("programs_input")->text().length() == 0)
			iNum = 0;
		else
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("programs_input")->text();
				iNum = ConvertToInt(buf, 1, 100);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе количества программ ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetCountOfPrograms(iNum);

		if (modeFlag == 'c')
			obj->SetProductID(Assortment::GetNewID());
		return true;
	}
	return false;
}

// Сохранить параметры мышки
bool EditMenu::SaveMouseParams(Mouse* obj)
{
	if (this->SaveExternalTechParams(obj))
	{
		QString buf;
		int iNum;
		if (this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("keys_input")->text().length() == 0)
			iNum = 0;
		else
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("keys_input")->text();
				iNum = ConvertToInt(buf, 1, 5);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе числа клавиш ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetCountOfButtons(iNum);

		if (!(this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("wheel_input")->text().length() == 0))
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("wheel_input")->text();
				CheckRussianLetters(&buf);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе типа колёсика ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetTypeOfWheel(buf);
		if (modeFlag == 'c')
			obj->SetProductID(Assortment::GetNewID());
		return true;
	}
	return false;
}

// Сохранить параметры клавиатуры
bool EditMenu::SaveKeyboardParams(Keyboard* obj)
{
	if (this->SaveExternalTechParams(obj))
	{
		QString buf;
		if (!(this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("keyboardtype_input")->text().length() == 0))
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("keyboardtype_input")->text();
				CheckRussianLetters(&buf);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе типа клавиатуры ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetTypeOfKeyboard(buf);

		if ((this->modeFlag == 'f' && this->child->findChild<QLineEdit*>("numpad_input")->text().length() == 0))
			this->child->findChild<QLineEdit*>("numpad_input")->setText(QChar(' '));
		else
		{
			try
			{
				buf = this->child->findChild<QLineEdit*>("numpad_input")->text();
				CheckExistence(&buf);
			}
			catch (InputExeption excep)
			{
				QString whereStr = "При вводе наличия нумпада ";
				excep.Show(this->child->findChild<QLabel*>("error_label"), &whereStr);
				return false;
			}
		}
		obj->SetNumpadExistense(this->child->findChild<QLineEdit*>("numpad_input")->text().toStdString()[0]);

		if (modeFlag == 'c')
			obj->SetProductID(Assortment::GetNewID());
		return true;
	}
	return false;
}



