#include "Mouse.h"
#include "MouseEditMenu.h"

const QString Mouse::TYPENAME = "Мышка";

// Сгенерировать описание
QString& Mouse::GenerateDescription(QString& str)
{
	dynamic_cast<ExternalTech*>(this)->GenerateDescription(str);
	str += "Тип колёсика: " + this->typeOfWheel + "\n";
	str += "Количество клавиш: " + QString::number(this->countOfButtons) + "\n";
	return str;
}
// Конструктор
Mouse::Mouse()
{
	this->countOfButtons = 0;
	this->typeOfWheel = "";
}
// Установить тип колёсика
void Mouse::SetTypeOfWheel(QString type) { this->typeOfWheel = type; }

// Установить количетство кнопок
void Mouse::SetCountOfButtons(int count) { this->countOfButtons = count; }

// Узнать тип колёсика
QString Mouse::GetTypeOfWheel() { return this->typeOfWheel; }

// Узнать количество кнопок
int Mouse::GetCountOFButtons() { return this->countOfButtons; }

// Открыть меню редактирования
QWidget* Mouse::OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric)
{
	MouseEditMenu* editMenu = new MouseEditMenu(this, mode, parent, showOnlyNumeric);
	editMenu->setGeometry(170, 30, editMenu->width(), editMenu->height());
	editMenu->show();
	return editMenu;
}
// Вернуть имя типа
const QString& Mouse::GetTypeName()
{
	return Mouse::TYPENAME;
}
// Сгенерировать полное описание
QString Mouse::GenerateDescription()
{
	QString description;
	this->GenerateDescription(description);
	return description;
}
// Вернуть функтор FilterComparator
Product::FilterComparator* Mouse::GetFilterComparator()
{
	return &this->comparator;
}
// Оператор сравнения
bool Mouse::operator==(Mouse& b)
{
	bool result = dynamic_cast<ExternalTech&>(*this) == b;
	if (result)
	{
		if (this->countOfButtons == b.countOfButtons && this->typeOfWheel == b.typeOfWheel) return true;
	}
	return false;
}
// Функция проверят obj на соотвествие фильтру
bool Mouse::MouseFilterComparator::operator()(Product* left, Product* obj, Product* right)
{
	Mouse* pLeft = dynamic_cast<Mouse*>(left);
	Mouse* pRight = dynamic_cast<Mouse*>(right);
	Mouse* pObj = dynamic_cast<Mouse*>(obj);
	// Проверка, что все 3 объекта принадлежат к классу мышки
	if (!pLeft || !pRight || !pObj) return false;
	Mouse result;
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

	// Проверка интерефейса подключения
	if (pObj->connectionInterface == pLeft->connectionInterface) result.connectionInterface = pLeft->connectionInterface;

	// Проеврка типа колёсика
	if (pObj->typeOfWheel == pLeft->typeOfWheel) result.typeOfWheel = pLeft->typeOfWheel;
	// Проверка числа кнопок
	if (pRight->countOfButtons != 0)
	{
		if (pLeft->countOfButtons < pObj->countOfButtons && pObj->countOfButtons < pRight->countOfButtons) result.countOfButtons = pLeft->countOfButtons;
	}
	else
		if (pLeft->countOfButtons < pObj->countOfButtons) result.countOfButtons = pLeft->countOfButtons;

	return result == *pLeft;
}

//
// Перегрузки ввода-вывода в файл
//
fstream& operator>>(fstream& in, Mouse& obj)
{
	in >> dynamic_cast<ExternalTech&>(obj);
	in.read(reinterpret_cast<char*>(&obj.countOfButtons), sizeof(int));
	in >> obj.typeOfWheel;
	return in;
}

fstream& operator<<(fstream& out, Mouse& obj)
{
	out << dynamic_cast<ExternalTech&>(obj);
	out.write(reinterpret_cast<char*>(&obj.countOfButtons), sizeof(int));
	out << obj.typeOfWheel;
	return out;
}
