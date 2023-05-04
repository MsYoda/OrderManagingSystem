#include "GPU.h"
#include "GPUEditMenu.h"

const QString GPU::TYPENAME = "Видеокарта";

// Сгенерировать описание
QString& GPU::GenerateDescription(QString& str)
{
	dynamic_cast<ComputerElement*>(this)->GenerateDescription(str);
	str += "Количество видеопамяти: " + QString::number(this->videoMemory) + "\n";
	str += "Тип памяти: " + this->typeOfMemory + "\n";
	return str;
}
// Конструктор
GPU::GPU() : ComputerElement()
{
	this->videoMemory = 0;
	this->typeOfMemory = "";
}
// Установить объём видеопамяти
void GPU::SetVideoMemory(int amount) { this->videoMemory = amount;  }

// Установить тип памяти
void GPU::SetTypeOfMemory(QString type) { this->typeOfMemory = type; }

// Узнать количество видеопамяти
int GPU::GetVideoMemory() { return this->videoMemory; }

// Узнать тип памяти
QString GPU::GetTypeOfMemory() { return this->typeOfMemory; }

// Открыть меню редактирования
QWidget* GPU::OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric)
{
	GPUEditMenu* editMenu = new GPUEditMenu(this, mode, parent, showOnlyNumeric);
	editMenu->setGeometry(170, 30, editMenu->width(), editMenu->height());
	editMenu->show();
	return editMenu;
}
// Вернуть имя типа
const QString& GPU::GetTypeName()
{
	return GPU::TYPENAME;
}
// Сгенерировать полное описание
QString GPU::GenerateDescription()
{
	QString description;
	this->GenerateDescription(description);
	return description;
}
// Вернуть функтор FilterComparator
Product::FilterComparator* GPU::GetFilterComparator()
{
	return &this->comparator;
}
// Оператор сравнения
bool GPU::operator==(GPU& b)
{
	bool result = dynamic_cast<ComputerElement&>(*this) == b;
	if (result)
	{
		if (this->typeOfMemory == b.typeOfMemory && this->videoMemory == b.videoMemory) return true;
	}
	return false;
}
// Функция проверят obj на соотвествие фильтру
bool GPU::GPUFilterComparator::operator()(Product* left, Product* obj, Product* right)
{
	GPU* pLeft = dynamic_cast<GPU*>(left);
	GPU* pRight = dynamic_cast<GPU*>(right);
	GPU* pObj = dynamic_cast<GPU*>(obj);

	// Проверка, что все 3 объекта принадлежат к классу видеокарты
	if (!pLeft || !pRight || !pObj) return false;
	GPU result;
	
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
	
	// Проверка видеопамяти
	if (pRight->videoMemory != 0)
	{
		if (pLeft->videoMemory < pObj->videoMemory && pObj->videoMemory < pRight->videoMemory) result.videoMemory = pLeft->videoMemory;
	}
	else
		if (pLeft->videoMemory < pObj->videoMemory) result.videoMemory = pLeft->videoMemory;

	// // Проверка типа видеопамяти
	if (pObj->typeOfMemory == pLeft->typeOfMemory) result.typeOfMemory = pLeft->typeOfMemory;

	return result == *pLeft;
}

//
// Перегрузки ввода-вывода в файл
//
fstream& operator>>(fstream& in, GPU& obj)
{
	in >> dynamic_cast<ComputerElement&>(obj);
	in.read(reinterpret_cast<char*>(&obj.videoMemory), sizeof(int));
	in >> obj.typeOfMemory;
	return in;
}

fstream& operator<<(fstream& out, GPU& obj)
{
	out << dynamic_cast<ComputerElement&>(obj);
	out.write(reinterpret_cast<char*>(&obj.videoMemory), sizeof(int));
	out << obj.typeOfMemory;
	return out;
}
