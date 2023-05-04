#pragma once
#include <qtablewidget.h>
#include <qheaderview.h>

class BaseTable :
	public QTableWidget
{
public:
	BaseTable(QWidget* parent = nullptr); // Конструктор, который задёт параметры таблиц
};

