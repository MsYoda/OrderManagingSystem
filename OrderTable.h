#pragma once
#include <qtablewidget.h>
#include "templates//BinaryTree.cpp"
#include "Order.h"
#include "Assortment.h"
#include "BaseTable.h"
#include "OrdersCollector.h"
#include <QMenu>
#include "Bank.h"

class OrderTable :
	public BaseTable
{
	Q_OBJECT
	QString username;   // Имя пользователя
	Bank* bank;         // Указатель на банк

public:
	OrderTable(QWidget* parent = nullptr);  // Конструктор

	void SetupTable(QString username, Bank* bank); // Установить поля таблицы

public slots:
	void UpdateTable();     // Обновить таблицу

	void CreateContextMenu(QPoint point);  // Создать контекстное меню

	void slotDenieOrder();          // Отменить заказ

signals:
	void userDenieOrder(QString username); // Сигнал о том, что пользователь отменил заказ
};

