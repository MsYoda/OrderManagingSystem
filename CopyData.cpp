#include "CopyData.h"

// Копирование данных с выделенем новой памяти
Product* CopyData(Product* data)
{

	// Огромное число проверок - проверка на тип указателя
	// записанного под Product*
	Product* copiedData = nullptr;
	if (dynamic_cast<CPU*>(data))
	{
		copiedData = new CPU;
		*(dynamic_cast<CPU*>(copiedData)) = *(dynamic_cast<CPU*>(data));
	}
	else if (dynamic_cast<GPU*>(data))
	{
		copiedData = new GPU;
		*(dynamic_cast<GPU*>(copiedData)) = *(dynamic_cast<GPU*>(data));
	}
	else if (dynamic_cast<Fridge*>(data))
	{
		copiedData = new Fridge;
		*(dynamic_cast<Fridge*>(copiedData)) = *(dynamic_cast<Fridge*>(data));
	}
	else if (dynamic_cast<Washmachine*>(data))
	{
		copiedData = new Washmachine;
		*(dynamic_cast<Washmachine*>(copiedData)) = *(dynamic_cast<Washmachine*>(data));
	}
	else if (dynamic_cast<Mouse*>(data))
	{
		copiedData = new Mouse;
		*(dynamic_cast<Mouse*>(copiedData)) = *(dynamic_cast<Mouse*>(data));
	}
	else if (dynamic_cast<Keyboard*>(data))
	{
		copiedData = new Keyboard;
		*(dynamic_cast<Keyboard*>(copiedData)) = *(dynamic_cast<Keyboard*>(data));
	}
	return copiedData;
}

// Копирование данных из source в destination
void CopyData(Product* source, Product* destination)
{
	// Огромное число проверок - проверка на тип указателя
	// записанного под Product*
	Product* copiedData = nullptr;
	if (dynamic_cast<CPU*>(source) && dynamic_cast<CPU*>(destination))
	{
		copiedData = destination;
		*(dynamic_cast<CPU*>(copiedData)) = *(dynamic_cast<CPU*>(source));
	}
	else if (dynamic_cast<GPU*>(source) && dynamic_cast<GPU*>(destination))
	{
		copiedData = destination;
		*(dynamic_cast<GPU*>(copiedData)) = *(dynamic_cast<GPU*>(source));
	}
	else if (dynamic_cast<Fridge*>(source) && dynamic_cast<Fridge*>(destination))
	{
		copiedData = destination;
		*(dynamic_cast<Fridge*>(copiedData)) = *(dynamic_cast<Fridge*>(source));
	}
	else if (dynamic_cast<Washmachine*>(source) && dynamic_cast<Washmachine*>(destination))
	{
		copiedData = destination;
		*(dynamic_cast<Washmachine*>(copiedData)) = *(dynamic_cast<Washmachine*>(source));
	}
	else if (dynamic_cast<Mouse*>(source) && dynamic_cast<Mouse*>(destination))
	{
		copiedData = destination;
		*(dynamic_cast<Mouse*>(copiedData)) = *(dynamic_cast<Mouse*>(source));
	}
	else if (dynamic_cast<Keyboard*>(source) && dynamic_cast<Keyboard*>(destination))
	{
		copiedData = destination;
		*(dynamic_cast<Keyboard*>(copiedData)) = *(dynamic_cast<Keyboard*>(source));
	}
}
