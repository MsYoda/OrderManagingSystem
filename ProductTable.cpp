#include "ProductTable.h"
#include "DeleteAction.h"
#include "EditAction.h"
#include "AddAction.h"
#include "CopyData.h"

// Конструктор
ProductTable::ProductTable(QWidget* parent) : BaseProductTable(parent)
{
	this->undoStack = nullptr;
	this->oldData = nullptr;
	QObject::connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(CreateContextMenu(QPoint)));
}

// Настроить стек отмены действий
void ProductTable::SetupUndoStack()
{
	this->undoStack = new QUndoStack(this);
	QAction* undoAction, *redoAction;
	undoAction = undoStack->createUndoAction(this);
	undoAction->setShortcuts(QKeySequence::Undo);
	this->addAction(undoAction);

	redoAction = undoStack->createRedoAction(this);
	redoAction->setShortcuts(QKeySequence::Redo);
	this->addAction(redoAction);
}

// Создать контекстное меню
void ProductTable::CreateContextMenu(QPoint point)
{
	QMenu* menu = new QMenu(this);
	/* Создаём действия для контекстного меню */
	QAction* editDevice = new QAction("Редактировать", this);
	QAction* deleteDevice = new QAction("Удалить", this);
	QAction* watchReviews = new QAction("Просмотреть отзывы", this);
	/* Подключаем СЛОТы обработчики для действий контекстного меню */
	QObject::connect(editDevice, SIGNAL(triggered()), this, SLOT(slotEditRecord()));     // Обработчик вызова диалога редактирования
	QObject::connect(deleteDevice, SIGNAL(triggered()), this, SLOT(slotRemoveRecord())); // Обработчик удаления записи
	QObject::connect(watchReviews, SIGNAL(triggered()), this, SLOT(slotOpenWatchReviewMenu()));
	/* Устанавливаем действия в меню */
	menu->addAction(editDevice);
	menu->addAction(deleteDevice);
	menu->addAction(watchReviews);
	this->CreateMenu(menu);
	/* Вызываем контекстное меню */
	menu->popup(QCursor::pos());
}

// Редактировать товар
void ProductTable::slotEditRecord()
{
	int id = this->item(this->currentRow(), 4)->text().toInt();
	Product* product = Assortment::GetByID(id);

	if (this->oldData) delete this->oldData;
	this->oldData = CopyData(product);

	QWidget* menu = product->OpenEditMenu('e', this->mainWindow);
}

// Удалить товар
void ProductTable::slotRemoveRecord()
{
	int id = this->item(this->currentRow(), 4)->text().toInt();
	this->undoStack->push(new DeleteAction(Assortment::GetByID(id), &Assortment::assortment, this));
	delete this->oldData;
	this->oldData = nullptr;
}

// Открыть меню отзывов
void ProductTable::slotOpenWatchReviewMenu()
{
	if (this->currentRow() != -1)
	{
		int id = this->item(this->currentRow(), 4)->text().toInt();
		emit openWatchReviewMenu(id);
	}
}

// Запомнить действие
void ProductTable::RememberAction(Product* obj, char action)
{
	if (action == 'e')
	{
		this->undoStack->push(new EditAction(obj, this->oldData, &Assortment::assortment, this));
		delete this->oldData;
		this->oldData = nullptr;
	}
	else if (action == 'c')
	{
		this->undoStack->push(new AddAction(obj, &Assortment::assortment, this));
	}
}
