#include "Keyboard.h"
#include "KeyboardEditMenu.h"

const QString Keyboard::TYPENAME = "Клавиатура";

// Сгенерировать описание
QString& Keyboard::GenerateDescription(QString& str)
{
	dynamic_cast<ExternalTech*>(this)->GenerateDescription(str);
	str += "Наличие нумапада: ";
	str.append(this->numbadExistence);
	str += "\nТип клавиатуры: " + this->typeOfKeyboard + "\n";
	return str;
}
// Конструктор
Keyboard::Keyboard()
{
	this->typeOfKeyboard = "";
	this->numbadExistence = ' ';
}
// Установить существование нумпада
void Keyboard::SetNumpadExistense(char exist) { this->numbadExistence = exist; }
// Установить тип клавиатуры
void Keyboard::SetTypeOfKeyboard(QString type) { this->typeOfKeyboard = type; }
// Узнать существование нумпада
char Keyboard::GetNumpadExistense() { return this->numbadExistence; }
// Узнать тип клавитуры
QString Keyboard::GetTypeOfKeyboard() { return this->typeOfKeyboard; }

// Открыть меню редактирования
QWidget* Keyboard::OpenEditMenu(char mode, QWidget* parent, bool showOnlyNumeric)
{
	KeyboardEditMenu* editMenu = new KeyboardEditMenu(this, mode, parent, showOnlyNumeric);
	editMenu->setGeometry(170, 30, editMenu->width(), editMenu->height());
	editMenu->show();
	return editMenu;
}
// Вернуть имя типа
const QString& Keyboard::GetTypeName()
{
	return Keyboard::TYPENAME;
}
// Сгенерировать полное описание
QString Keyboard::GenerateDescription()
{
	QString description;
	this->GenerateDescription(description);
	return description;
}
// Вернуть функтор FilterComparator
Product::FilterComparator* Keyboard::GetFilterComparator()
{
	return &this->comparator;
}
// Оператор сравнения
bool Keyboard::operator==(Keyboard& b)
{
	bool result = dynamic_cast<ExternalTech&>(*this) == b;
	if (result)
	{
		if (this->numbadExistence == b.numbadExistence && this->typeOfKeyboard == b.typeOfKeyboard) return true;
	}
	return false;
}
// Функция проверят obj на соотвествие фильтру
bool Keyboard::KeyboardFilterComparator::operator()(Product* left, Product* obj, Product* right)
{
	Keyboard* pLeft = dynamic_cast<Keyboard*>(left);
	Keyboard* pRight = dynamic_cast<Keyboard*>(right);
	Keyboard* pObj = dynamic_cast<Keyboard*>(obj);
	// Проверка, что все 3 объекта принадлежат к классу клавиатуры
	if (!pLeft || !pRight || !pObj) return false;
	Keyboard result;
	// Проерка названия
	if (pObj->name.startsWith(pLeft->name, Qt::CaseInsensitive)) result.name = pLeft->name;
	// Для числовых данных проверка зависит от наличия правой границы фильтра!
	// Проверка цен
	if (pRight->cost != 0)
	{
		if (pLeft->cost < pObj->cost && pObj->cost < pRight->cost) result.cost = pLeft->cost;
	}
	else
		if (pLeft->cost < pObj->cost) result.cost = pLeft->cost;

	// Проверка интерефейса подключения
	if (pObj->connectionInterface == pLeft->connectionInterface) result.connectionInterface = pLeft->connectionInterface;

	// Проверка существования нумпада и типа клавитуры
	if (pObj->numbadExistence == pLeft->numbadExistence) result.numbadExistence = pLeft->numbadExistence;
	if (pObj->typeOfKeyboard == pLeft->typeOfKeyboard) result.typeOfKeyboard = pLeft->typeOfKeyboard;

	return result == *pLeft;

}

//
// Перегрузки ввода-вывода в файл
//
fstream& operator>>(fstream& in, Keyboard& obj)
{
	in >> dynamic_cast<ExternalTech&>(obj);
	in.read(reinterpret_cast<char*>(&obj.numbadExistence), sizeof(char));
	in >> obj.typeOfKeyboard;
	return in;
}

fstream& operator<<(fstream& out, Keyboard& obj)
{
	out << dynamic_cast<ExternalTech&>(obj);
	out.write(reinterpret_cast<char*>(&obj.numbadExistence), sizeof(char));
	out << obj.typeOfKeyboard;
	return out;
}
