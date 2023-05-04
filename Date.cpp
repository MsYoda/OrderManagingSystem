#include "Date.h"
// Конструктор
Date::Date()
{
	this->day = 0; this->month = 0; this->year = 0;
}
// Контруктор с параметрами
Date::Date(int day, int month, int year)
{
	this->day = day; this->month = month; this->year = year;
}
// Оператор равно
bool Date::operator==(const Date& b)
{
	return this->day == b.day && this->month == b.month && this->year == b.year;
}
// Оператор не равно
bool Date::operator!=(const Date& b)
{
	return !(*this == b);
}
// Оператор меньше
bool Date::operator<(Date& b)
{
	// Сравниваем в порядке год->месяц->день
	if (this->year < b.year) return true;
	else if (this->year > b.year) return false;
	else
	{
		if (this->month < b.month) return true;
		else if (this->month > b.month) return false;
		else
		{
			if (this->day < b.day) return true;
			else return false;
		}
	}
}
// Оператор больше
bool Date::operator>(Date& b)
{
	// Сравниваем в порядке год->месяц->день
	if (this->year > b.year) return true;
	else if (this->year < b.year) return false;
	else
	{
		if (this->month > b.month) return true;
		else if (this->month < b.month) return false;
		else
		{
			if (this->day > b.day) return true;
			else return false;
		}
	}
}
