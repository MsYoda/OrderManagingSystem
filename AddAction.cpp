#include "AddAction.h"

// Конструктор
AddAction::AddAction(Product* obj, BinaryTree<Product*>* tree, BaseProductTable* tableToUpdate, QUndoCommand* command)
	: QUndoCommand(command)
{
	this->newObj = CopyData(obj);
	this->tree = tree;
	this->tableToUpdate = tableToUpdate;
}

// Деструктор
AddAction::~AddAction()
{
	delete this->newObj;
}

// Отмена действия
void AddAction::undo()
{
	// Удаляем добавленный товар
	for (BinaryTree<Product*>::Iterator it = tree->Begin(); it != tree->End(); it++)
	{
		if (this->newObj->GetID() == (*it)->GetID())
		{
			delete (*it);
			tree->RemoveData(&(*it));
			break;
		}
	}
	tableToUpdate->UpdateTable();
}

// Отмена отмены действия
void AddAction::redo()
{
	// Добавляем товар обратно
	Product* objToTree = CopyData(this->newObj);
	tree->AddData(objToTree);
	tableToUpdate->UpdateTable();
}
