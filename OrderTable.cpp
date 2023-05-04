#include "OrderTable.h"

// Конструктор
OrderTable::OrderTable(QWidget* parent) : BaseTable(parent)
{
	this->username = nullptr;
	QObject::connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(CreateContextMenu(QPoint)));
}

// Установить поля таблицы
void OrderTable::SetupTable(QString username, Bank* bank)
{
	this->username = username;
	this->bank = bank;
}

// Обновить таблицу
void OrderTable::UpdateTable()
{
	BinaryTree<Order*>::Iterator it = OrdersCollector::orders.Begin();
	this->setRowCount(0);

	for (int i = 0; it != OrdersCollector::orders.End(); it++, i++)
	{
		// Выводим только заказы текущего пользователя
		if ((*it)->GetUsername() == username)
		{
			this->insertRow(i);
			QString structureText;
			int orderCost = 0;
			Order* currentOrder = *it;
			// Цикл по составу заказа
			// Генерируется текст состава заказа, а также его стоимость
			for (int j = 0; j < currentOrder->GetCountOfProduts(); j++)
			{
				int id = (*currentOrder)[j].product.GetID();
				Product obj = (*currentOrder)[j].product;
				structureText += (*currentOrder)[j].typeName + ":\n"; // ????

				structureText += obj.GetName() + " x " + QString::number((*currentOrder)[j].countOFProduct) + "\n";
				orderCost += obj.GetCost() * (*currentOrder)[j].countOFProduct;
			}
			structureText[structureText.length() - 1] = QChar('\0');

			// Заполнение таблицы
			QTableWidgetItem* item;
			item = new QTableWidgetItem;
			item->setFlags(item->flags() & ~Qt::ItemIsEditable);
			item->setData(Qt::DisplayRole, structureText);
			this->setItem(i, 0, item);

			item = new QTableWidgetItem;
			item->setFlags(item->flags() & ~Qt::ItemIsEditable);
			item->setData(Qt::DisplayRole, orderCost);
			this->setItem(i, 1, item);

			item = new QTableWidgetItem(currentOrder->GetOrderState());
			item->setFlags(item->flags() & ~Qt::ItemIsEditable);
			this->setItem(i, 2, new QTableWidgetItem(currentOrder->GetOrderState()));;

			item = new QTableWidgetItem;
			item->setFlags(item->flags() & ~Qt::ItemIsEditable);
			item->setData(Qt::DisplayRole, (*it)->GetID());
			this->setItem(i, 3, item);;

		}
		else
		{
			i--;
		}
	}
	this->resizeRowsToContents();
}

// Контекстное меню
void OrderTable::CreateContextMenu(QPoint point)
{
	QMenu* menu = new QMenu(this);
	///* Создаём действия для контекстного меню */
	QAction* denieOrder = new QAction("Отменить заказ", this);
	///* Подключаем СЛОТы обработчики для действий контекстного меню */
	QObject::connect(denieOrder, SIGNAL(triggered()), this, SLOT(slotDenieOrder()));     // Обработчик вызова диалога редактирования
	///* Устанавливаем действия в меню */
	menu->addAction(denieOrder);
	///* Вызываем контекстное меню */
	menu->popup(QCursor::pos());
}

// Отменить заказ
void OrderTable::slotDenieOrder()
{
	if (this->currentRow() != -1)
	{
		int id = this->item(this->currentRow(), 3)->data(Qt::DisplayRole).toInt();
		Order* order = OrdersCollector::GetOrderByID(id);
		if (order->GetOrderState() != Order::GetStateNameByID(Order::deniedByUser))
		{
			order->SetOrderState(Order::deniedByUser);
			this->setItem(this->currentRow(), 2, new QTableWidgetItem(order->GetOrderState()));
			Transaction transaction = Transaction("admin", order->GetUsername(), -1 * order->GetSum());
			this->bank->AddTransaction(transaction);
			emit userDenieOrder(this->username);
		}
	}
}