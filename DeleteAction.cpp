#include "DeleteAction.h"
#include "Products.h"
#include "CopyData.h"

// Конструктор
DeleteAction::DeleteAction(Product* obj, BinaryTree<Product*> *tree, BaseProductTable* tableToUpdate, QUndoCommand* command)
	: QUndoCommand(command)
{
	this->table = tableToUpdate;
	this->tree = tree;
	this->deletedObj = nullptr;
	this->deletedObj = CopyData(obj);
}

// Деструктор
DeleteAction::~DeleteAction()
{
	if (this->deletedObj) delete this->deletedObj;
}

// Отмена действия
void DeleteAction::undo()
{
	// Добавляем элмент обратно в контейнер
	Product* obj = CopyData(this->deletedObj);
	this->tree->AddData(obj);
	this->table->UpdateTable();
}

// Отмена отмены действия
void DeleteAction::redo()
{
	// Удаляем товар из контейнера
	for (BinaryTree<Product*>::Iterator it = tree->Begin(); it != tree->End(); it++)
	{
		if ((*it)->GetID() == this->deletedObj->GetID())
		{
			delete(*it);
			tree->RemoveData(&(*it));
			break;
		}
	}
	this->table->UpdateTable();
}
