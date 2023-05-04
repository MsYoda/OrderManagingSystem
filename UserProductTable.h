#pragma once
#include "BaseProductTable.h"
#include <QMenu>
#include <qobject.h>

class UserProductTable : public BaseProductTable
{
	Q_OBJECT

public:
	UserProductTable(QWidget* parent = nullptr); // Конструктор
public slots:
	void CreateContextMenu(QPoint point);	// Создать контекстное меню
	void slotAddToChart();			// Добавить товар в корзину
	void slotOpenNewReviewMenu();	// Открыть меню написания нового отзывы
	void slotOpenWatchReviewMenu();	// Открыть меню просмотра отзывов

signals:
	void addedItemToBacket(int id);		// Товар был добавлен в корзину
	void openReviewMenu(int productID);	// Было запрошено открытие меню отзывов
};

