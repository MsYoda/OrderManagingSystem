#pragma once
#include <QString>
#include <fstream>

// Перегрузки ввода-вывода для QString
std::fstream& operator>>(std::fstream& in, QString& obj);
std::fstream& operator<<(std::fstream& out, QString& obj);