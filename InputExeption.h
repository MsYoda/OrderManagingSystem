#pragma once
#include "Exception.h"

class InputExeption : public MyException
{
public:
	InputExeption(QString text = "Ошибка при вводе, попробуйте ещё раз!"); // Конструктор

	void Show(QLabel* showObj, QString* addtionalString = nullptr) override; // Показать ошибку
	const QString& GetMessage() override; // Вернуть сообщение ошибки
};

