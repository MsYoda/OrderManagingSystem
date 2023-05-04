#include "EditAction.h"

// Конструктор
EditAction::EditAction(Product* oldObj, Product* newObj, BinaryTree<Product*>* tree, BaseProductTable* tableToUpdate, QUndoCommand* command)
	: QUndoCommand(command)
{
	this->tree = tree;
	this->tableToUpdate = tableToUpdate;
	this->oldObj = CopyData(oldObj);
	this->newObj = CopyData(newObj);
}

// Деструктор
EditAction::~EditAction()
{
	delete this->oldObj;
	delete this->newObj;
}

// Отмена действия
void EditAction::undo()
{
	// Устанавливаем old в контейнер и меняем местами old и new
	Product* tmp = CopyData(this->newObj);
	for (BinaryTree<Product*>::Iterator it = tree->Begin(); it != tree->End(); it++)
	{
		if ((*it)->GetID() == this->oldObj->GetID())
		{
			CopyData(this->oldObj, this->newObj);
			CopyData(this->oldObj, (*it));
			CopyData(tmp, this->oldObj);
			delete tmp;
			break;
		}
	}
	tableToUpdate->UpdateTable();
}

// Отмена отмены действия
void EditAction::redo()
{
	this->undo();
}
