#include "CheckFunctions.h"
#include "InputExeption.h"

// Конвертация строки в число
int ConvertToInt(QString& var, int lBorder, int rBorder)
{
	bool correct = false;
	int num = 0;
	num = var.toInt(&correct); // Перевод строки в число
	if (!correct)
	{
		// Есвли введено не число, то генериуется исключение
		throw InputExeption("допущена ошибка!.\nВведено не число!");
	}
	else // Проверки на соотвествие числа границам
	{
		if (num < lBorder) throw InputExeption("допущена ошибка!\n Введено число меньше " + QString::number(lBorder));
		if (num > rBorder) throw InputExeption("допущена ошибка!\n Введено число больше " + QString::number(rBorder));
	}
	return num;
}

// Перевол строки в дробь
float ConvertToFloat(QString& var, float lBorder, float rBorder)
{
	bool correct = false;
	float num = 0;
	num = var.toFloat(&correct);
	if (!correct)
	{
		// Есвли введено не число, то генериуется исключение
		throw InputExeption("допущена ошибка!\n Введено не число!");
	}
	else // Проверки на соотвествие числа границам
	{
		if (num < lBorder) throw InputExeption("допущена ошибка!\n Введено число меньше " + QString::number(lBorder));
		if (num > rBorder) throw InputExeption("допущена ошибка!\n Введено число больше " + QString::number(rBorder));
	}
	return num;
}

// Проверка числа на соотвествии границам
void CheckInt(int var, int lBorder, int rBorder)
{
	if (var < lBorder) throw InputExeption("допущена ошибка!\n Введено число меньше " + QString::number(lBorder));
	if (var > rBorder) throw InputExeption("допущена ошибка!\n Введено число больше " + QString::number(rBorder));
}

// Парсинг строки вида XX.XX.XXXX в дату
Date ConvertToDate(QString* str)
{
	Date date;
	QString buf;

	// Конвертируются первые 2 символа
	int i = 0;
	for (i = 0; (i < 3 && i < (*str).length()) && (*str)[i] != QChar('.')  ; i++)
	{
		buf.append((*str)[i]);
	}
	bool ok = false;
	int iNum;
	iNum = buf.toInt(&ok);

	// Если в считанных символах находится не число или оно не подходит под границы дня
	// то генериуются исключения
	if (!ok) throw InputExeption("допущена ошибка.\nПроверьте ввод дня!");
	if (iNum < 1 || iNum > 31) throw InputExeption("допущена ошибка.\nВвод дня должен находится в пределах от 1 до 31!");
	date.day = iNum;

	buf.clear();
	i++;

	// Конвертируются следующие 2 символа
	for (; i < (*str).length() && (*str)[i] != QChar('.') && i < 6 ; i++)
	{
		buf.append((*str)[i]);
	}
	// Если в считанных символах находится не число или оно не подходит под границы месяца
	// то генериуются исключения
	iNum = buf.toInt(&ok);
	if (!ok) throw InputExeption("допущена ошибка.\nПроверьте ввод месяца!");
	if (iNum < 1 || iNum > 12) throw InputExeption("допущена ошибка.\nВвод месяца должен находится в пределах от 1 до 12!");
	date.month = iNum;

	i++;
	buf.clear();
	// Считываются последние 4 символа
	for (; i < str->length() && i < 10; i++)
	{
		buf.append((*str)[i]);
	}
	// Если в считанных символах находится не число или оно не подходит под границы года
	// то генериуются исключения
	iNum = buf.toInt(&ok);
	if (!ok || i < str->length()) throw InputExeption("допущена ошибка.\nПроверьте ввод года!");
	if (iNum < 0) throw InputExeption("допущена ошибка.\nВвод года не может быть отрицательным!");
	date.year = iNum;

	return date;
}

// Провеока строки, сотстоящей из английских букв
void CheckEngLetters(QString* str)
{
	if (str->length() == 0) throw InputExeption("допущена ошибка.\nНе введено ни одного символа!");
	for (int i = 0; i < str->length(); i++)
	{
		if (!((*str)[i].toLower() >= QChar('a') && (*str)[i].toLower() <= QChar('z')))
			throw InputExeption("допущена ошибка.\nВведены не англйиские буквы!");
	}
}
// Проверка строки, сотстоящей из английских букв и спец. символов
void CheckEngString(QString* str)
{
	if (str->length() == 0) throw InputExeption("допущена ошибка.\nНе введено ни одного символа!");
	for (int i = 0; i < str->length(); i++)
	{
		// 1072 - код 'а'; 1103 - код 'я'
		if (((*str)[i].toLower() >= QChar(1072) && (*str)[i].toLower() <= QChar(1103)))
			throw InputExeption("допущена ошибка.\nВведены русские буквы!");
	}
}

// Проверка строки состоящей из букв русского алфавита
void CheckRussianLetters(QString* str)
{
	for (int i = 0; i < str->length(); i++)
	{
		// 1072 - код 'а'; 1103 - код 'я'
		if (!((*str)[i].toLower() >= QChar(1072) && (*str)[i].toLower() <= QChar(1103)))
			throw InputExeption("допущена ошибка.\nВведены символы отличные от русских букв!");
	}
}

// Проверить поле, отвечающее за "сущестование" характеристики
void CheckExistence(QString* str)
{
	if (str->length() > 1) throw InputExeption("допущена ошибка.\nДолжен быть введён только + или -");
	if (str->length() < 1) throw InputExeption("допущена ошибка.\nНе введено ничего!");
	if ((*str)[0] != QChar('+') && (*str)[0] != QChar('-')) throw InputExeption("допущена ошибка.\nДолжен быть введён только + или -");
}
