#include "BacketTable.h"
#include "CopyData.h"
#include "algorithm.cpp"

// Контструктор
BacketTable::BacketTable(QWidget* parent) : QTableWidget(parent)
{
	QObject::connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(CreateContextMenu(QPoint)));
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setFocusPolicy(Qt::NoFocus);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
}

// Создать контекстное меню
void BacketTable::CreateContextMenu(QPoint point)
{
	QMenu* menu = new QMenu(this);
	///* Создаём действия для контекстного меню */
	QAction* removeFromChart = new QAction("Удалить", this);
	///* Подключаем СЛОТы обработчики для действий контекстного меню */
	QObject::connect(removeFromChart, SIGNAL(triggered()), this, SLOT(slotRemoveFromChart()));     // Обработчик вызова диалога редактирования
	///* Устанавливаем действия в меню */
	menu->addAction(removeFromChart);
	///* Вызываем контекстное меню */
	menu->popup(QCursor::pos());
}

// Удалить товар из корзины
void BacketTable::slotRemoveFromChart()
{
	if (this->currentRow() != -1)
	{
		ProductCount toDel;
		toDel.countOFProduct = this->item(this->currentRow(), 2)->text().toInt();
		unsigned int id = this->item(this->currentRow(), 4)->text().toInt();
		toDel.product = *(Assortment::GetByID(id));
		if (toDel.countOFProduct > 1)
		{
			ProductCount& finded = *(container::find_if(backet.Begin(), backet.End(), [&](ProductCount obj) { return obj == toDel; }));
			finded.countOFProduct -= 1;
		}
		else
		{
			backet.RemoveData(&toDel);
		}
		this->UpdateTable();
	}
}

// Сформировать заказ
void BacketTable::CreateOrder()
{
	Order* newOrder = new Order;
	BinaryTree<ProductCount>::Iterator it = backet.Begin();
	int i;
	for (i = 0; it != backet.End(); it++, i++)
	{
		newOrder->AddProduct((*it));
	}
	newOrder->SetOrderState(Order::inProgress);
	newOrder->SetID(OrdersCollector::GetNewID());

	QLabel* messageLabel;
	messageLabel = this->parentWidget()->parentWidget()->parentWidget()->findChild<QLabel*>("create_order_error_label");

	// Если корзина пуста, то заказ добавить нельзя
	if (i != 0)
	{
		emit orderCreated(newOrder);
		backet.ClrTree();
		this->UpdateTable();
		messageLabel->setStyleSheet("color : rgb(0, 0, 0)");
		messageLabel->setText("Заказ сформирован успешно!");
	}
	else
	{
		messageLabel->setStyleSheet("color : rgb(255, 0, 0)");
		messageLabel->setText("Заказ не сформирован, вы не добавили ничего в корзину!");
		delete newOrder;
	}
}

// Обновить таблицу
void BacketTable::UpdateTable()
{
	this->setRowCount(0);
	BinaryTree<ProductCount>::Iterator it = backet.Begin();
	int orderSum = 0;
	for (int i = 0; it != backet.End(); it++, i++)
	{
		this->insertRow(i);
		Product obj = (*it).product;

		QTableWidgetItem* item = new QTableWidgetItem((*it).typeName);
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		this->setItem(i, 0, item);

		item = new QTableWidgetItem(obj.GetName());
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		this->setItem(i, 1, item);
		
		item = new QTableWidgetItem(QString::number((*it).countOFProduct));
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		this->setItem(i, 2, item);

		item = new QTableWidgetItem(QString::number(obj.GetCost()));
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		this->setItem(i, 3, item);

		item = new QTableWidgetItem(QString::number(obj.GetID()));
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		this->setItem(i, 4, item);

		orderSum += obj.GetCost() * (*it).countOFProduct;
	}
	this->parentWidget()->parentWidget()->parentWidget()->findChild<QLabel*>("orderSum")->setText(QString::number(orderSum) + "$");

}

// Очистить таблицу
void BacketTable::ClearTable()
{
	backet.ClrTree();
	this->setRowCount(0);
}

// Добавить товар в корзину
void BacketTable::AddToBacket(int id)
{
	ProductCount orderLine;
	orderLine.product = *(Assortment::GetByID(id));
	orderLine.typeName = Assortment::GetByID(id)->GetTypeName();
	for (BinaryTree<ProductCount>::Iterator it = backet.Begin(); it != backet.End(); it++)
	{
		if ((*it).product.GetID() == orderLine.product.GetID())
		{
			(*it).countOFProduct++;
			return;
		}
	}
	orderLine.countOFProduct = 1;
	backet.AddData(orderLine);
}