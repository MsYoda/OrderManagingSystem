#include "ContainerException.h"

// Конструктор
ContainerException::ContainerException(QString text)
{
	this->message = text;
}
// Показать ошибку
void ContainerException::Show(QLabel* showObj, QString* additionalStr)
{
	if (additionalStr)
		showObj->setText(*additionalStr + this->message);
	else
		showObj->setText(this->message);
}
// Вернуть сообщение ошибки
const QString& ContainerException::GetMessage()
{
	return this->message;
}
