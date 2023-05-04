#include "Transaction.h"

// Конструктор
Transaction::Transaction()
{
	this->sender = "";
	this->receiver = "";
	this->sum = 0;
}
// Конструктор с параметрами
Transaction::Transaction(QString sender, QString receiver, int sum)
{
	this->sender = sender;
	this->receiver = receiver;
	this->sum = sum;
}
//
// Операторы ввода/вывода в файл
//
fstream& operator<<(fstream& out, Transaction& obj)
{
	out << obj.sender;
	out << obj.receiver;
	out.write(reinterpret_cast<char*>(&obj.sum), sizeof(int));
	return out;
}

fstream& operator>>(fstream& in, Transaction& obj)
{
	in >> obj.sender;
	in >> obj.receiver;
	in.read(reinterpret_cast<char*>(&obj.sum), sizeof(int));
	return in;
}
