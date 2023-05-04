#include "UserProductTable.h"
#include "ReviewWriteWidget.h"

// Конструктор
UserProductTable::UserProductTable(QWidget* parent) : BaseProductTable(parent)
{
	QObject::connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(CreateContextMenu(QPoint)));
}

// Создать контекстное меню
void UserProductTable::CreateContextMenu(QPoint point)
{
	QMenu* menu = new QMenu(this);
	///* Создаём действия для контекстного меню */
	QAction* addToChart = new QAction("Добавить в корзину", this);
	QAction* writeReview = new QAction("Написать отзыв", this);
	QAction* watchReviews = new QAction("Просмотреть отзывы", this);
	///* Подключаем СЛОТы обработчики для действий контекстного меню */
	QObject::connect(addToChart, SIGNAL(triggered()), this, SLOT(slotAddToChart()));     // Обработчик вызова диалога редактирования
	QObject::connect(writeReview, SIGNAL(triggered()), this, SLOT(slotOpenNewReviewMenu()));
	QObject::connect(watchReviews, SIGNAL(triggered()), this, SLOT(slotOpenWatchReviewMenu()));
	///* Устанавливаем действия в меню */
	menu->addAction(addToChart);
	menu->addAction(writeReview);
	menu->addAction(watchReviews);
	this->CreateMenu(menu);
	///* Вызываем контекстное меню */
	menu->popup(QCursor::pos());
}

// Добавить товар в корзину
void UserProductTable::slotAddToChart()
{
	if (this->currentRow() != -1)
	{
		int id = this->item(this->currentRow(), 4)->text().toInt();
		emit addedItemToBacket(id);
	}
}

// Открыть меню написания отзыва
void UserProductTable::slotOpenNewReviewMenu()
{
	if (this->currentRow() != -1)
	{
		int id = this->item(this->currentRow(), 4)->text().toInt();
		emit openReviewMenu(id);
	}
}

// Открыть меню просмотра отзывов
void UserProductTable::slotOpenWatchReviewMenu()
{
	if (this->currentRow() != -1)
	{
		int id = this->item(this->currentRow(), 4)->text().toInt();
		emit openWatchReviewMenu(id);
	}
}