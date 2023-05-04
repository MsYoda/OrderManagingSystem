#include "InputExeption.h"
#include <iostream>

using namespace std;

// Исключение при вводе
InputExeption::InputExeption(QString text)
{
	this->message = text;
}

// Показ ошибки
void InputExeption::Show(QLabel* showObj, QString* additionalStr)
{
	showObj->setStyleSheet("color: rgb(255, 0, 0)");
	if (additionalStr)
		showObj->setText(*additionalStr + message);
	else showObj->setText(message);
}

// Вернуть текст сообщения
const QString& InputExeption::GetMessage()
{
	return this->message;
}
