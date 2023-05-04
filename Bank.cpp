#include "Bank.h"
// Добавить сумму на счёт
void Bank::AddCash(int sum)
{
	this->cash += sum;
}
// Добавить транзацию в историю
void Bank::AddTransaction(Transaction transaction)
{
	this->cash += transaction.sum;
	this->transactionHistory.push_back(transaction);
}
// Вернуть итератор на конец истории операций
std::vector<Transaction>::iterator Bank::GetTransactionsEnd()
{
	return this->transactionHistory.end();
}
// Вернуть деньги на счету
int Bank::GetCash()
{
	return this->cash;
}
// Вернуть операцию с индексом ind
Transaction Bank::operator[](int ind)
{
	return this->transactionHistory[ind];
}
// Вернуть итератор на начало истории опеараций
std::vector<Transaction>::iterator Bank::GetTransactionsBegin()
{
	return this->transactionHistory.begin();
}

// Перегрузки ввода/вывода
fstream& operator<<(fstream& out, Bank& obj)
{
	unsigned int size = 0;
	size = obj.transactionHistory.size();
	out.write(reinterpret_cast<char*>(&obj.cash), sizeof(int));
	out.write(reinterpret_cast<char*>(&size), sizeof(int));
	for (vector<Transaction>::iterator it = obj.transactionHistory.begin(); it != obj.transactionHistory.end(); it++)
	{
		out << *it;
	}
	return out;
}

fstream& operator>>(fstream& in, Bank& obj)
{
	unsigned int len = 0;
	in.read(reinterpret_cast<char*>(&obj.cash), sizeof(int));
	in.read(reinterpret_cast<char*>(&len), sizeof(int));

	for (unsigned int i = 0; i < len; i++)
	{
		Transaction transaction;
		in >> transaction;
		obj.transactionHistory.push_back(transaction);
	}
	return in;
}
