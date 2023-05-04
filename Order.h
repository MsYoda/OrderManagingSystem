#pragma once
#include <QtCore/qstring.h>
#include <vector>
#include "ioqstring.h"
#include "Assortment.h"

#define ORDER_STATES_COUNT 5

struct ProductCount // Элкмент заказа
{
	int countOFProduct; // Количество товара
	Product product; // Товар
	QString typeName; // Имя типа товара

	// Операторы сравнения
	bool operator==(ProductCount& b);
	bool operator>(ProductCount& b);
	bool operator<(ProductCount& b);
	bool operator<=(ProductCount& b);
	bool operator>=(ProductCount& b);
	bool operator!=(ProductCount& b);

	ProductCount(); // Конструктор

	// Чтение/запись в файл
	friend std::fstream& operator>>(std::fstream& in, ProductCount& obj);
	friend std::fstream& operator<<(std::fstream& out, ProductCount& obj);
};


class Order
{
	QString username;	// Имя пользователя
	std::vector<ProductCount> orderStructure; // Содержимое заказа
	static const QString orderStates[ORDER_STATES_COUNT]; // Статусы заказа
	int orderState; // Номер состояния заказа
	int id;	// ID заказа

public:
	Order(); // Конструктор
	enum OrderStatesInd { denied, inProgress, ready, accepted, deniedByUser }; // Статусы заказа

	void SetUsername(QString name); // Установить имя пользователя
	void SetOrderState(int orderState); // Установить статус заказа по номеру
	void SetOrderState(QString orderState); // Установить статус заказ строкой
	void AddProduct(ProductCount orderString); // Добавить продукт
	void RemoveProduct(int id);
	void SetID(int id); // Установить ID

	QString GetUsername(); // Вернуть имя пользователя
	int GetCountOfProduts(); // Вернуть количество продукта
	QString GetOrderState(); // Вернуть состояние заказа
	int GetID(); // Вернуть ID
	int GetSum(); // Вернуть сумму заказа

	ProductCount operator[](int ind); // Получить элемент заказа по ID

	static QString GetStateNameByID(int id); // Получить текст сотояния заказа по номеру

	// Опеарторы ввода/вывода
	friend std::fstream& operator>>(std::fstream& in, Order& obj);
	friend std::fstream& operator<<(std::fstream& out, Order& obj);
};

