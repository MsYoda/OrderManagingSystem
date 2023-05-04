#pragma once
#include "BaseTable.h"
#include "Order.h"
#include "OrdersCollector.h"
#include "Assortment.h"
#include "User.h"
#include "templates//BinaryTree.cpp"
#include <qtoolbutton.h>
#include "qlayout.h"
#include "OrderStateMenu.h"
#include "Order.h"
#include "Bank.h"

class AdminOrderTable :
	public BaseTable
{
	BinaryTree<User>* users;    // Указатель на контейнер с пользовтаелями
	Bank* bank;         // Указатель на банк

public:
	AdminOrderTable(QWidget* parent = nullptr); // Конструктор

	void SetupTable(BinaryTree<User>* users, Bank* bank); // Установить основные поля таблицы

	QWidget* CreateOrderStateButton(QString text, int orderID);	// Создать кнопку выбора состояния заказа
   
public slots:

	void IncreaseRating(QString username);		// Увеличить рейтинг пользователя
	void UpdateTable();		// Обновить таблицу

signals:
	void orderAccepted(QString username);	// Сигнал о том, что заказ забран полльзователем
};

