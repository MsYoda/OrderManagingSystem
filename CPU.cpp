#include "CPU.h"
#include "CPUEditMenu.h"

const QString CPU::TYPENAME = "Процессор";

// Сгенерировать описание
QString& CPU::GenerateDescription(QString& str)
{
	dynamic_cast<ComputerElement*>(this)->GenerateDescription(str);
	str += "Частота процессора: " + QString::number(this->speed) + " GHz\n";
	str += "Число ядер: " + QString::number(this->countOfCores) + "\n";
	return str;
}

// Конструктор
CPU::CPU() : ComputerElement()
{
	this->countOfCores = 0;
	this->speed = 0;
}
// Установить частоту
void CPU::SetSpeed(float speed) { this->speed = speed; }
// Установить количество ядер
void CPU::SetCountOfCores(int count) { this->countOfCores = count; }
// Узнать частоту
float CPU::GetSpeed() { return this->speed; }
// Узнать количество ядер
int CPU::GetCountOfCores() { return this->countOfCores;  }
// Открыть меню редактирования
QWidget* CPU::OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric)
{
	CPUEditMenu* editMenu = new CPUEditMenu(this, mode, parent, showOnlyNumeric);
	editMenu->setGeometry(170, 30, editMenu->width(), editMenu->height());
	editMenu->show();
	return editMenu;
}
// Вернуть имя типа
const QString& CPU::GetTypeName()
{
	return CPU::TYPENAME;
}
// Сгенерировать полное описание
QString CPU::GenerateDescription()
{
	QString description;
	this->GenerateDescription(description);
	return description;
}
// Вернуть функтор FilterComparator
Product::FilterComparator* CPU::GetFilterComparator()
{
	return &this->comparator;
}
// Оператор сравнения
bool CPU::operator==(CPU& b)
{
	bool result = dynamic_cast<ComputerElement&>(*this) == b;
	if (result)
	{
		if (this->countOfCores == b.countOfCores && this->speed == b.speed) return true;
	}
	return false;
}

// Функция проверят obj на соотвествие фильтру с границми left и right
bool CPU::CPUFilterComparator::operator()(Product* left, Product* obj, Product* right)
{
	CPU* pLeft = dynamic_cast<CPU*>(left);
	CPU* pRight = dynamic_cast<CPU*>(right);
	CPU* pObj = dynamic_cast<CPU*>(obj);
	
	// Проверка, что все 3 объекта принадлежат к классу процессора
	if (!pLeft || !pRight || !pObj) return false;
	CPU result;

	// Проерка названия
	if (pObj->name.startsWith(pLeft->name, Qt::CaseInsensitive)) result.name = pLeft->name;
	
	// Для числовых данных проверка зависит от наличия правой границы фильтра!
	// Проверка цены
	if (pRight->cost != 0)
	{
		if (pLeft->cost < pObj->cost && pObj->cost < pRight->cost) result.cost = pLeft->cost;
	}
	else 
		if (pLeft->cost < pObj->cost) result.cost = pLeft->cost;;

	// Проверка режима "разгона"
	if (pObj->boostMode == pLeft->boostMode) result.boostMode = pLeft->boostMode;
	Date nullDate(0, 0, 0);
	// Проверка даты
	if (pRight->dateOfRelease != nullDate)
	{
		if (pLeft->dateOfRelease < pObj->dateOfRelease && pObj->dateOfRelease < pRight->dateOfRelease) result.dateOfRelease = pLeft->dateOfRelease;
	}
	else 
		if (pLeft->dateOfRelease < pObj->dateOfRelease) result.dateOfRelease = pLeft->dateOfRelease;

	// Проверка числа ядер
	if (pRight->countOfCores != 0)
	{
		if (pLeft->countOfCores < pObj->countOfCores && pObj->countOfCores < pRight->countOfCores) result.countOfCores = pLeft->countOfCores;
	}
	else 
		if (pLeft->countOfCores < pObj->countOfCores) result.countOfCores = pLeft->countOfCores;

	// Проверка частоты
	if (pRight->speed != 0)
	{
		if (pLeft->speed < pObj->speed && pObj->speed < pRight->speed) result.speed = pLeft->speed;
	}
	else 
		if (pLeft->speed < pObj->speed)  result.speed = pLeft->speed;

	return result == *pLeft;
}

//
// Операторы чтения/записи в файл
//
fstream& operator>>(fstream& in, CPU& obj)
{
	in >> dynamic_cast<ComputerElement&>(obj);
	in.read(reinterpret_cast<char*>(&obj.countOfCores), sizeof(int));
	in.read(reinterpret_cast<char*>(&obj.speed), sizeof(float));
	return in;
}

fstream& operator<<(fstream& out, CPU& obj)
{
	out << dynamic_cast<ComputerElement&>(obj);
	out.write(reinterpret_cast<char*>(&obj.countOfCores), sizeof(int));
	out.write(reinterpret_cast<char*>(&obj.speed), sizeof(float));
	return out;
}

