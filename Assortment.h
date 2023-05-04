#pragma once
#include "Product.h"
#include "templates/BinaryTree.cpp"
#include "BinaryFile.cpp"

class Assortment
{
private:
	static unsigned int nextID; // Следующий ID товара

public:
	static BinaryTree<Product*> assortment; // Контейнер с товарами
	static unsigned int GetNewID(); // Сгенерировать новый ID
	static void CheckID(Product* product); // Проверка является ли ID продукта больше текущего nextID
	static Product* GetByID(unsigned int id); // Вернуть товар по ID
	static void DeleteByID(unsigned int id); // Удалить товар по ID

	// Загрузить ассортимент из файла
	template <typename T>
	static void LoadAssortmentFromFile(BinaryFile<T> &file)
	{
		file.OpenForReading();
		if (file.IsOpen())
		{
			while (1)
			{
				T* obj = new T;
				*obj = file.ReadObj();
				if (file.IsEndOfFile())
				{
					delete obj;
					break;
				}
				// При считыании из файла, необходимо постоянно обновлять nextID
				if (obj->GetID() > nextID) nextID = obj->GetID();
				Assortment::assortment.AddData(obj);
			}
			file.Close();
		}
	}

};

