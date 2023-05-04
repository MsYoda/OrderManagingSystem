#pragma once
#include <QString>
#include "Date.h"

void CheckEngLetters(QString* str); // Проверка на наличие только английских букв в строке
void CheckEngString(QString* str); // Проверка на наличие только аенглийских букв и спец-символов
void CheckRussianLetters(QString* str); // проверка на наличие только русских букв
void CheckExistence(QString* str); // Проверка правильно ли введено сущестовавание

int ConvertToInt(QString& var, int lBorder, int rBorder); // Конвертация строки в число
float ConvertToFloat(QString& var, float lBorder, float rBorder); // Конвертация строки в дробь

void CheckInt(int var, int lBorder, int rBorder); // Проверка числа на границы

Date ConvertToDate(QString* str); // Конверитьровать строку вида xx.xx.xxxx в дату