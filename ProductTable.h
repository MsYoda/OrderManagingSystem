#pragma once
#include "BaseProductTable.h"
#include <QMenu>
#include <QUndoStack>

class ProductTable : public BaseProductTable
{
	Q_OBJECT
	QUndoStack* undoStack;		// Стек для отмены действий
	Product* oldData;			// Старая информация при редактировании

public:
	ProductTable(QWidget* parent = nullptr);	// Конструктор

	void SetupUndoStack();	// Настроить стек отмены действий

public slots:
	void CreateContextMenu(QPoint point);	// Создать контекстное меню

	void slotEditRecord();	// Редактировать товар

	void slotRemoveRecord();	// Удалить товар

	void slotOpenWatchReviewMenu();	// Открыть меню отзывов
	void RememberAction(Product* obj, char action); // Запомнить действие
};

