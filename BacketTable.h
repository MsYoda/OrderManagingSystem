#pragma once
#include <qtablewidget.h>
#include "templates//BinaryTree.cpp"
#include "Order.h"
#include "Assortment.h"
#include "OrdersCollector.h"
#include <QMenu>
#include <qlabel.h>

class BacketTable :
	public QTableWidget
{
	Q_OBJECT
	BinaryTree<ProductCount> backet;    // Контейнера с товарами в корзине

public:
	BacketTable(QWidget* parent = nullptr); //Контструктор

public slots:
	void CreateContextMenu(QPoint point);   // Создать контекстное меню

	void slotRemoveFromChart();     // Удалить товар из корзины

	void CreateOrder();             // Сформировать заказ

	void UpdateTable();     // Обновить таблицу
	void ClearTable();      // Очистить таблицу

	void AddToBacket(int id);   // Добавить товар в корзину

signals:
	void orderCreated(Order* order);    // Сигнал о том, что заказ сформирован
};

