#pragma once
struct Date
{
	int day; // День
	int month; // Месяц
	int year; // Год

	Date(); // Конструктор
	Date(int day, int month, int year); // Контруктор с параметрами
	// Операторы сравнения
	bool operator<(Date& b);
	bool operator>(Date& b);
	bool operator==(const Date& b);
	bool operator!=(const Date& b);

};

