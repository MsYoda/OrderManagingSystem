#include "FileException.h"

// Конструктор
FileException::FileException(QString text)
{
	this->message = text;
}
// Показать ошибку
void FileException::Show(QLabel* showObj, QString* additionalStr)
{
	if (additionalStr)
		showObj->setText(*additionalStr + this->message);
	else
		showObj->setText(this->message);
}

// Вернуть сообщение ошибки
const QString& FileException::GetMessage()
{
	return this->message;
}
