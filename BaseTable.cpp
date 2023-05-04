#include "BaseTable.h"

// Конструктор
BaseTable::BaseTable(QWidget* parent) : QTableWidget(parent)
{
    this->verticalHeader()->setVisible(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setFocusPolicy(Qt::NoFocus);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
}
