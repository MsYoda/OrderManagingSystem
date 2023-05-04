#pragma once
#include <qundostack.h>
#include "Product.h"
#include "templates//BinaryTree.cpp"
#include "BaseProductTable.h"
#include "CopyData.h"

class EditAction : // Команда редактировать товар
	public QUndoCommand
{
	Product* oldObj; // Объект до редактирования
	Product* newObj; // Объект после редактирования
	BinaryTree<Product*>* tree;  // Указатель на контейнер с товарами
	BaseProductTable* tableToUpdate; // Указатель на таблицу, которую нужно обновить

public:
	// Конструктор, инициализирующий все необходимые данные
	EditAction(Product* oldObj, Product* newObj, BinaryTree<Product*>* tree, BaseProductTable* tableToUpdate, QUndoCommand* command = nullptr);
	~EditAction();

	void undo() override; // Отменить действие
	void redo() override; // Отменить отмену действия
};

