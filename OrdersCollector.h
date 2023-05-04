#pragma once
#include "templates/BinaryTree.cpp"
#include "Order.h"
#include "BinaryFile.cpp"

class OrdersCollector
{
	static unsigned int nextID; // Следующий ID заказа

public:
	static BinaryTree<Order*> orders; // Контейнер с заказами

	static int GetNewID(); // Сгенерировать новый ID
	static Order* GetOrderByID(int id); // Вернуть заказ по ID
	static void DeleteByID(int id); // Удалить заказ по ID

	static void WriteOrdersToFile(BinaryFile<Order>& file); // Записать все заказы в файл
	static void ReadOrdersFromFile(BinaryFile<Order>& file); // Прочитать все заказы из файла
};

