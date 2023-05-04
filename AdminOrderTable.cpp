#include "AdminOrderTable.h"

// Конструктор
AdminOrderTable::AdminOrderTable(QWidget* parent) : BaseTable(parent)
{
	this->bank = nullptr;
	this->users = nullptr;
	this->setColumnWidth(3, 170);
}

// Установить основные поля таблицы
void AdminOrderTable::SetupTable(BinaryTree<User>* users, Bank* bank)
{
	this->users = users;
	this->bank = bank;
}

// Создать кнопку выбора состояния заказа
QWidget* AdminOrderTable::CreateOrderStateButton(QString text, int orderID)
{
	OrderStateMenu* menu = new OrderStateMenu(this);
	menu->setObjectName("order_state_menu");
	menu->SetOrderID(orderID);
	menu->setMinimumSize(130, 25);
	QWidget* wgt = new QWidget;
	wgt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QHBoxLayout* l = new QHBoxLayout;

	QToolButton* btn = new QToolButton;
	btn->setText(text);
	btn->setPopupMode(QToolButton::InstantPopup);
	btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	btn->setGeometry(0, 0, 120, 25);
	btn->setStyleSheet("color: black; background-color: white");

	AdminOrderTable* table = this;

	// Автоматически генерируются пункты для контекстного меню изменения состояния заказа
	for (int i = 0; i < ORDER_STATES_COUNT; i++)
	{
		QAction* action;
		action = menu->addAction(Order::GetStateNameByID(i));
		connect(action, &QAction::triggered, this, [=]()
			{
				OrderStateMenu* parentMenu = qobject_cast<OrderStateMenu*>(action->parentWidget());
				Order* order = OrdersCollector::GetOrderByID(parentMenu->GetOrderID());

				if (action->text() != order->GetOrderState())
				{
					order->SetOrderState(action->text());
					// Увеличить рейтинг пользователю, есои он забрал заказ
					if (order->GetOrderState() == Order::GetStateNameByID(Order::accepted))
					{
						this->IncreaseRating(order->GetUsername());
					}
					// Уменьшить деньги на счету в случае отмены заказа пользователю
					else if (order->GetOrderState() == Order::GetStateNameByID(Order::denied))
					{
						Transaction transaction = Transaction("admin", order->GetUsername(), -1 * order->GetSum());
						this->bank->AddTransaction(transaction);
					}
					btn->setText(action->text());
				}
			});

	}
	btn->setMenu(menu);
	l->setContentsMargins(10, 5, 10, 5);
	l->addSpacing(0);
	l->addWidget(btn);

	wgt->setLayout(l);
	wgt->setGeometry(0, 0, 120, 25);
	return wgt;
}

// Увелить рейтиенг пользователю
void AdminOrderTable::IncreaseRating(QString username)
{
	for (BinaryTree<User>::Iterator it = this->users->Begin(); it != this->users->End(); it++)
	{
		if ((*it).GetUserName() == username)
		{
			(*it).SetRating((*it).GetRating() + 1);
			break;
		}
	}
}

// Обновить таблицу
void AdminOrderTable::UpdateTable()
{
	BinaryTree<Order*>::Iterator it = OrdersCollector::orders.Begin();
	this->setRowCount(0);

	// Цикл по всем заказам
	for (int i = 0; it != OrdersCollector::orders.End(); it++, i++)
	{
		this->insertRow(i);
		QString structureText;
		int orderCost = 0;
		Order* currentOrder = *it;
		// Цикл по составу заказа
		for (int j = 0; j < currentOrder->GetCountOfProduts(); j++)
		{
			Product obj = (*currentOrder)[j].product;
			structureText += obj.GetName() + " x " + QString::number((*currentOrder)[j].countOFProduct) + "\n";
			orderCost += obj.GetCost() * (*currentOrder)[j].countOFProduct;
		}
		structureText[structureText.length() - 1] = QChar('\0');

		// Заполнение строки таблицы
		QTableWidgetItem* item;
		item = new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setData(Qt::DisplayRole, structureText);
		this->setItem(i, 0, item);

		this->setItem(i, 1, new QTableWidgetItem(currentOrder->GetUsername()));;

		item = new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setData(Qt::DisplayRole, orderCost);
		this->setItem(i, 2, item);

		this->setCellWidget(i, 3, this->CreateOrderStateButton(currentOrder->GetOrderState(), (*it)->GetID()));

		item = new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setData(Qt::DisplayRole, (*it)->GetID());
		this->setItem(i, 4, item);;
	}
	this->resizeRowsToContents();
}
