#include "Fridge.h"
#include "FridgeEditMenu.h"

const QString Fridge::TYPENAME = "Холодильник";

// Сгенерировать описание
QString& Fridge::GenerateDescription(QString& str)
{
	dynamic_cast<HouseTech*>(this)->GenerateDescription(str);
	str += "Объём камеры: " + QString::number(this->cameraVolume) + " дм3\n";
	str += "Уровень шума: " + QString::number(this->noiseLevel) + " Db\n";
	return str;
}
// Конструктор
Fridge::Fridge()
{
	this->cameraVolume = 0;
	this->noiseLevel = 0;
}
// Установить объём камеры
void Fridge::SetCameraVolume(float vol) { this->cameraVolume = vol; }
// Установить уровень шума
void Fridge::SetNoiseLevel(float lvl) { this->noiseLevel = lvl; }
// Узнать объём камеры
float Fridge::GetCameraVolume() { return this->cameraVolume; }
// Узнать уровень шума
float Fridge::GetNoiseLevel() { return this->noiseLevel; }

// Вернуть функтор FilterComparator
Product::FilterComparator* Fridge::GetFilterComparator()
{
	return &this->comparator;
}
// Оператор сравнения
bool Fridge::operator==(Fridge& b)
{
	bool result = dynamic_cast<HouseTech&>(*this) == b;
	if (result)
	{
		if (this->noiseLevel == b.noiseLevel && this->cameraVolume == b.cameraVolume) return true;
	}
	return false;
}
// Открыть меню редактирования
QWidget* Fridge::OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric)
{
	FridgeEditMenu* editMenu = new FridgeEditMenu(this, mode, parent, showOnlyNumeric);
	editMenu->setGeometry(170, 10, editMenu->width(), editMenu->height());
	editMenu->show();
	return editMenu;
}
// Вернуть имя типа
const QString& Fridge::GetTypeName()
{
	return Fridge::TYPENAME;
}
// Сгенерировать полное описание
QString Fridge::GenerateDescription()
{
	QString description;
	this->GenerateDescription(description);
	return description;
}
// Функция проверят obj на соотвествие фильтру
bool Fridge::FridgeFilterComparator::operator()(Product* left, Product* obj, Product* right)
{
	Fridge* pLeft = dynamic_cast<Fridge*>(left);
	Fridge* pRight = dynamic_cast<Fridge*>(right);
	Fridge* pObj = dynamic_cast<Fridge*>(obj);

	// Проверка, что все 3 объекта принадлежат к классу холодильника
	if (!pLeft || !pRight || !pObj) return false;
	Fridge result;
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

	// Проверка уровня шума
	if (pRight->noiseLevel != 0)
	{
		if (pLeft->noiseLevel < pObj->noiseLevel && pObj->noiseLevel < pRight->noiseLevel) result.noiseLevel = pLeft->noiseLevel;
	}
	else
		if (pLeft->noiseLevel < pObj->noiseLevel) result.noiseLevel = pLeft->noiseLevel;

	// Проверка объёма камеры
	if (pRight->cameraVolume != 0)
	{
		if (pLeft->cameraVolume < pObj->cameraVolume && pObj->cameraVolume < pRight->cameraVolume) result.cameraVolume = pLeft->cameraVolume;
	}
	else
		if (pLeft->cameraVolume < pObj->cameraVolume) result.cameraVolume = pLeft->cameraVolume;

	return result == *pLeft;
}

//
// Перегрузки ввода-вывода в файл
//
fstream& operator>>(fstream& in, Fridge& obj)
{
	in >> dynamic_cast<HouseTech&>(obj);
	in.read(reinterpret_cast<char*>(&obj.noiseLevel), sizeof(float));
	in.read(reinterpret_cast<char*>(&obj.cameraVolume), sizeof(float));
	return in;
}

fstream& operator<<(fstream& out, Fridge& obj)
{
	out << dynamic_cast<HouseTech&>(obj);
	out.write(reinterpret_cast<char*>(&obj.noiseLevel), sizeof(float));
	out.write(reinterpret_cast<char*>(&obj.cameraVolume), sizeof(float));
	return out;
}
