#include "OrdersCollector.h"

unsigned int OrdersCollector::nextID = 0;
BinaryTree<Order*> OrdersCollector::orders;

// Сгенерировать новый ID
int OrdersCollector::GetNewID()
{
	OrdersCollector::nextID++;
	return OrdersCollector::nextID;
}

// Вернуть заказ по ID
Order* OrdersCollector::GetOrderByID(int id)
{
	for (BinaryTree<Order*>::Iterator it = OrdersCollector::orders.Begin(); it != OrdersCollector::orders.End(); it++)
	{
		if ((*it)->GetID() == id) return (*it);
	}
	return nullptr;
}

// Удалить заказ по ID
void OrdersCollector::DeleteByID(int id)
{
	for (BinaryTree<Order*>::Iterator it = OrdersCollector::orders.Begin(); it != OrdersCollector::orders.End(); it++)
	{
		if ((*it)->GetID() == id)
		{
			delete (*it);
			OrdersCollector::orders.RemoveData(&(*it));
			break;
		}
	}
}
// Записать все заказы в файл
void OrdersCollector::WriteOrdersToFile(BinaryFile<Order>& file)
{
	file.OpenForWriting();
	if (file.IsOpen())
	{
		for (BinaryTree<Order*>::Iterator it = OrdersCollector::orders.Begin(); it != OrdersCollector::orders.End(); it++)
		{
			file.WriteObj(*it);
		}
		file.Close();
	}
}
// Прочитать все заказы из файла
void OrdersCollector::ReadOrdersFromFile(BinaryFile<Order>& file)
{
	file.OpenForReading();
	if (file.IsOpen())
	{
		while (!file.IsEndOfFile())
		{
			Order* obj = new Order;
			*obj = file.ReadObj();
			if (file.IsEndOfFile())
			{
				delete obj;
				break;
			}
			if (obj->GetID() > OrdersCollector::nextID) OrdersCollector::nextID = obj->GetID();
			OrdersCollector::orders.AddData(obj);
		}
		file.Close();
	}
}
