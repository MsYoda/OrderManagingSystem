#include "Assortment.h"
#include "algorithm.cpp"

unsigned int Assortment::nextID = 0;
BinaryTree<Product*> Assortment::assortment;

// Сгенерировать новый ID
unsigned int Assortment::GetNewID()
{
	Assortment::nextID++;
	return Assortment::nextID;
}
// Проверка является ли ID продукта больше текущего nextID
void Assortment::CheckID(Product* product) { if (product->GetID() > Assortment::nextID) Assortment::nextID = product->GetID(); }

// Вернуть товар по ID
Product* Assortment::GetByID(unsigned int id)
{
	Product* finded;
	auto findedIter = container::find_if(Assortment::assortment.Begin(), Assortment::assortment.End(), [&](Product* obj)
		{
			if (obj->GetID() == id) return true;
			else return false;
		});
	if (findedIter != Assortment::assortment.End()) return *findedIter;
	return nullptr;
}

// Удалить товар по ID
void Assortment::DeleteByID(unsigned int id)
{
	auto findedIter = container::find_if(Assortment::assortment.Begin(), Assortment::assortment.End(), [&](Product* obj)
		{
			if (obj->GetID() == id) return true;
			else return false;
		});
	if (findedIter != Assortment::assortment.End()) delete (*findedIter);
}
