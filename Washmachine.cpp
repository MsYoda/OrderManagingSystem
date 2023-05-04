#include "Washmachine.h"
#include "WashMachineEditMenu.h"

const QString Washmachine::TYPENAME = "Стиральная машина";

// Сгенерировать описание
QString& Washmachine::GenerateDescription(QString& str)
{
	dynamic_cast<HouseTech*>(this)->GenerateDescription(str);
	str += "Максимальная загрузка: " + QString::number(this->maxWeight) + "\n";
	str += "Количество программ: " + QString::number(this->countOfPrograms) + "\n";
	return str;
}
// Конструктор
Washmachine::Washmachine()
{
	this->countOfPrograms = 0;
	this->maxWeight = 0;
}
// Установить максимальную загрузку
void Washmachine::SetMaxWeight(float num) { this->maxWeight = num; }

// Установить число программ
void Washmachine::SetCountOfPrograms(int count) { this->countOfPrograms = count; }

// Узнать максимальную загрузку
float Washmachine::GetMaxWeight() { return this->maxWeight; }

// Установить число программ
int Washmachine::GetCountOfPrograms() { return this->countOfPrograms; }

// Открыть меню редактирования
QWidget* Washmachine::OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric)
{
	WashMachineEditMenu* editMenu = new WashMachineEditMenu(this, mode, parent, showOnlyNumeric);
	editMenu->setGeometry(170, 30, editMenu->width(), editMenu->height());
	editMenu->show();
	return editMenu;
}

// Вернуть имя типа
const QString& Washmachine::GetTypeName()
{
	return Washmachine::TYPENAME;
}

// Сгенерировать полное описание
QString Washmachine::GenerateDescription()
{
	QString description;
	this->GenerateDescription(description);
	return description;
}

// Вернуть функтор FilterComparator
Product::FilterComparator* Washmachine::GetFilterComparator()
{
	return &this->comparator;
}

// Оператор сравнения
bool Washmachine::operator==(Washmachine& b)
{
	bool result = dynamic_cast<HouseTech&>(*this) == b;
	if (result)
	{
		if (this->maxWeight == b.maxWeight && this->countOfPrograms == b.countOfPrograms) return true;
	}
	return false;
}

// Функция проверят obj на соотвествие фильтру
bool Washmachine::WashMacineFilterComparator::operator()(Product* left, Product* obj, Product* right)
{
	Washmachine* pLeft = dynamic_cast<Washmachine*>(left);
	Washmachine* pRight = dynamic_cast<Washmachine*>(right);
	Washmachine* pObj = dynamic_cast<Washmachine*>(obj);
	// Проверка, что все 3 объекта принадлежат к классу стиральной машины
	if (!pLeft || !pRight || !pObj) return false;
	Washmachine result;
	// Проерка названия
	if (pObj->name.startsWith(pLeft->name, Qt::CaseInsensitive)) result.name = pLeft->name;
	// Для числовых данных проверка зависит от наличия правой границы фильтра!
	// Проверка цены
	if (pRight->cost != 0)
	{
		if (pLeft->cost < pObj->cost && pObj->cost < pRight->cost) result.cost = pLeft->cost;
	}
	else
		if (pLeft->cost < pObj->cost) result.cost = pLeft->cost;

	// Проверка класса энергопотребления и размещения
	if (pObj->classOFConsuming == pLeft->classOFConsuming) result.classOFConsuming = pLeft->classOFConsuming;
	if (pObj->placement == pLeft->placement) result.placement = pLeft->placement;

	// Проверка максимальной загрузки
	if (pRight->maxWeight != 0)
	{
		if (pLeft->maxWeight < pObj->maxWeight && pObj->maxWeight < pRight->maxWeight) result.maxWeight = pLeft->maxWeight;
	}
	else
		if (pLeft->maxWeight < pObj->maxWeight) result.maxWeight = pLeft->maxWeight;

	// Проверка количества программ
	if (pRight->countOfPrograms != 0)
	{
		if (pLeft->countOfPrograms < pObj->countOfPrograms && pObj->countOfPrograms < pRight->countOfPrograms) result.countOfPrograms = pLeft->countOfPrograms;
	}
	else
		if (pLeft->countOfPrograms < pObj->countOfPrograms) result.countOfPrograms = pLeft->countOfPrograms;


	return result == *pLeft;
}

//
// Перегрузки ввода-вывода в файл
//
fstream& operator>>(fstream& in, Washmachine& obj)
{
	in >> dynamic_cast<HouseTech&>(obj);
	in.read(reinterpret_cast<char*>(&obj.countOfPrograms), sizeof(int));
	in.read(reinterpret_cast<char*>(&obj.maxWeight), sizeof(float));
	return in;
}

fstream& operator<<(fstream& out, Washmachine& obj)
{
	out << dynamic_cast<HouseTech&>(obj);
	out.write(reinterpret_cast<char*>(&obj.countOfPrograms), sizeof(int));
	out.write(reinterpret_cast<char*>(&obj.maxWeight), sizeof(float));
	return out;
}