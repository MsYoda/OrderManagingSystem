#pragma once
#include "Exception.h"

class ContainerException :
	public MyException
{
public:
	ContainerException(QString text = "Ошибка в работе контейнера!"); // Конструктор

	void Show(QLabel* showObj, QString* additionalStr) override; // Показать ошибку
	const QString& GetMessage() override; // Вернуть сообщение ошибки
};

