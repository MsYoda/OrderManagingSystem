#pragma once
#include <qundostack.h>
#include "CopyData.h"
#include "templates///BinaryTree.cpp"
#include "BaseProductTable.h"

class AddAction : // Команда добавить товар
	public QUndoCommand
{
	Product* newObj; // Новый объект
	BinaryTree<Product*>* tree; // Указатель на контейнер с товарами
	BaseProductTable* tableToUpdate; // Указатель на таблицу, которую нужно обновить
public:
	// Конструктор, инициализирующий все необходимые данные
	AddAction(Product* obj, BinaryTree<Product*>* tree, BaseProductTable* tableToUpdate, QUndoCommand* command = nullptr);
	~AddAction();

	void undo() override; // Отменить действие
	void redo() override; // Отменить отмену действия
};

