#pragma once
#include "string.h"
#include <qstring.h>
#include <qlabel.h>

// Класс исключений
class MyException
{
protected:
	QString message; // Текст сообщения

public:
	// Показать ошибку
	virtual void Show(QLabel* showObj = nullptr, QString* additionalStr = nullptr) = 0;
	virtual const QString& GetMessage() = 0; // Вернуть текст ошибки
};

