#pragma once
#include <QTableWidget>
#include <QLabel>
#include <qpushbutton.h>
#include "Assortment.h"
#include "BaseTable.h"
#include <QDialog>
//#include "OrderSystem.h"
#include "qmainwindow.h"

class BaseProductTable :
	public BaseTable
{
	Q_OBJECT
protected:

	QWidget* mainWindow;	// Главное окно программы

	QDialog* descriptionWidget = nullptr;	// Виджет с описанием товара

	Product* leftFilterBorder = nullptr;	// Левая граница фильтра
	Product* rightFilterBorder = nullptr;	// Правая граница фильтра

public slots:
	void AddString(int i, Product* obj);	// Добавить строку в таблицу

	void UpdateTable();	// Обновить таблицу

	void OpenDescription(const QModelIndex& index);	// Открыть описание
	void slotSortByRising();						// Сортировать по возрастанию цены
	void slotSortByDecreasing();					// Сортировать по убыванию цены

	void CreateMenu(QMenu* menu);					// Создать меню сортировки

public:
	void SetFilter(Product* newFilterLeft, Product* newFilterRight);	// Установить фильтр
	void CreateFilterMenu();	// Создать меню фильтра
	void EditFilter();			// Редактировать фильтр

	void DeleteFilter();		// Удалить фильтр

	void SetMainWidget(QWidget* parent);	// Установить виджет главного окна

	BaseProductTable(QWidget* parent);		// Конструктор
	~BaseProductTable();					// Декструктор
signals:
	void openWatchReviewMenu(int productID); // Сигнал для открытия меню отзывов
};

