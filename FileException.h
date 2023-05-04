#pragma once
#include "Exception.h"

class FileException :
	public MyException
{
public:
	FileException(QString text = "Ошибка в работе c файлом!"); // Конструктор

	void Show(QLabel* showObj, QString* additionalStr) override;  // Показать ошибку
	const QString& GetMessage() override; // Вернуть сообщение ошибки
};

