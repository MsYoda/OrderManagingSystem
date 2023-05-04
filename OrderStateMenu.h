#pragma once
#include <QMenu>

class OrderStateMenu :
	public QMenu
{
	Q_OBJECT
	int orderID; // ID заказа

public:
	OrderStateMenu(QWidget* parent = nullptr); // Конструктор
	void SetOrderID(int id);        // Установить номер заказа
	int GetOrderID();           // Получить номер заказа
};

