#include "OrderStateMenu.h"

// Конструктор
OrderStateMenu::OrderStateMenu(QWidget* parent) : QMenu(parent)
{
	orderID = 0;
}
// Установить номер заказа
void OrderStateMenu::SetOrderID(int id)
{
	this->orderID = id;
}
// Получить номер заказа
int OrderStateMenu::GetOrderID()
{
	return this->orderID;
}
