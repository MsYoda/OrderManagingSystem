#include "Order.h"
#include "ContainerException.h"

// Статусы заказа
const QString Order::orderStates[] = { "Отменён", "В обработке", "Готов к выдаче", "Получен заказчиком", "Отменён пользователем"};

// Конструктор
Order::Order()
{
	this->username = "";
	this->orderState = -1;
}
// Установить имя пользователя
void Order::SetUsername(QString name) { this->username = name; }

// Установить статус заказа по номеру
void Order::SetOrderState(int orderState) { this->orderState = orderState; }

// Установить статус заказ строкой
void Order::SetOrderState(QString orderState)
{ 
	for (int i = 0; i < ORDER_STATES_COUNT; i++)
	{
		if (this->orderStates[i] == orderState)
		{
			this->orderState = i;
			break;
		}
	}
}

// Добавить продукт
void Order::AddProduct(ProductCount orderString)
{
	this->orderStructure.push_back(orderString);
}

// Установить ID
void Order::SetID(int id) { this->id = id; }

// Вернуть имя пользователя
QString Order::GetUsername() { return this->username; }

// Вернуть количество продуктов
int Order::GetCountOfProduts()
{
	return this->orderStructure.size();
}
// Вернуть состояние заказа
QString Order::GetOrderState()
{
	return Order::orderStates[this->orderState];
}
// Вернуть ID
int Order::GetID() { return this->id ; }

// Вернуть сумму заказа
int Order::GetSum()
{
	int sum = 0;
	for (int j = 0; j < this->GetCountOfProduts(); j++)
	{
		Product obj = (*this)[j].product;
		sum += obj.GetCost() * (*this)[j].countOFProduct;
	}
	return sum;
}

// Получить текст сотояния заказа по номеру
QString Order::GetStateNameByID(int id)
{
	if (id > -1 && id < ORDER_STATES_COUNT)
		return Order::orderStates[id];
	else return QString();
}


// Получить элемент заказа по ID
ProductCount Order::operator[](int ind)
{
	if (ind >= this->orderStructure.size() || ind < 0) throw ContainerException("Out of vector range!");
	return this->orderStructure[ind];
}


// Оператор равно
bool ProductCount::operator==(ProductCount& b)
{
	if (this->countOFProduct == b.countOFProduct && this->product.GetID() == b.product.GetID()) return true;
	else return false;
}

// Оператор больше
bool ProductCount::operator>(ProductCount& b)
{
	if (this->product.GetID() > b.product.GetID()) return true;
	else return false;
}
// Оператор меньше
bool ProductCount::operator<(ProductCount& b)
{
	if (this->product.GetID() < b.product.GetID()) return true;
	else return false;
}

// Оператор меньше или равно
bool ProductCount::operator<=(ProductCount& b)
{
	return *this < b || *this == b;
}
// Оператор больше или равно
bool ProductCount::operator>=(ProductCount& b)
{
	return *this > b || *this == b;
}
// Оператор не равно
bool ProductCount::operator!=(ProductCount& b)
{
	return !(*this == b);
}
// Контрсуктор
ProductCount::ProductCount()
{
	this->countOFProduct = 0;
}


//
// Чтение/запись заказа из файла
//
std::fstream& operator>>(std::fstream& in, Order& obj)
{
	in >> obj.username;
	in.read(reinterpret_cast<char*>(&obj.id), sizeof(int));
	in.read(reinterpret_cast<char*>(&obj.orderState), sizeof(int));
	int size = 0;
	in.read(reinterpret_cast<char*>(&size), sizeof(int));
	for (int i = 0; i < size; i++)
	{
		ProductCount lineOfOrder;
		in >> lineOfOrder;
		obj.orderStructure.push_back(lineOfOrder);
	}
	return in;
}

std::fstream& operator<<(std::fstream& out, Order& obj)
{
	out << obj.username;
	out.write(reinterpret_cast<char*>(&obj.id), sizeof(int));
	out.write(reinterpret_cast<char*>(&obj.orderState), sizeof(int));
	int size = obj.orderStructure.size();
	out.write(reinterpret_cast<char*>(&size), sizeof(int));
	for (int i = 0; i < size; i++)
	{
		out << obj.orderStructure[i];
	}
	return out;
}
//------------------

//
// Чтение/запись строки заказа из файла
//
std::fstream& operator>>(std::fstream& in, ProductCount& obj)
{
	in.read(reinterpret_cast<char*>(&obj.countOFProduct), sizeof(int));
	in >> obj.product;
	in >> obj.typeName;
	return in;
}

std::fstream& operator<<(std::fstream& out, ProductCount& obj)
{
	out.write(reinterpret_cast<char*>(&obj.countOFProduct), sizeof(int));
	out << obj.product;
	out << obj.typeName;
	return out;
}
