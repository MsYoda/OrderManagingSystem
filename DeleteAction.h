#pragma once
#include <QUndoCommand>
#include "Product.h"
#include "templates//BinaryTree.cpp"
#include "BaseProductTable.h"

class DeleteAction : // Команда удалить товар
    public QUndoCommand
{
    Product* deletedObj; // Удалённый объект
    BinaryTree<Product*>* tree; // Указатель на контейнер с товарами
    BaseProductTable* table; // Указатель на таблицу, которую нужно обновить

public:
    // Конструктор, инициализирующий все необходимые данные
    DeleteAction(Product* obj, BinaryTree<Product*> *tree, BaseProductTable* tableToUpdate, QUndoCommand* command = nullptr);
    ~DeleteAction();

    void undo() override; // Отменить действие
    void redo() override; // Отменить отмену действия
};

