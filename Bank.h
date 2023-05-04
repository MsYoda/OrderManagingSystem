#pragma once
#include "Transaction.h"
#include <vector>
#include <fstream>

using namespace std;

class Bank
{
	int cash = 0; // Деньги на счёте
	vector<Transaction> transactionHistory; // История операций

public:
	void AddCash(int sum); // Добавить сумму на счёт
	void AddTransaction(Transaction transaction); // Добавить транзацию в историю

	int GetCash();	// Вернуть деньги на счету
	vector<Transaction>::iterator GetTransactionsBegin(); // Вернуть итератор на начало истории опеараций
	vector<Transaction>::iterator GetTransactionsEnd(); // Вернуть итератор на конец истории операций

	Transaction operator[] (int ind); // Вернуть операцию с индексом ind

	// Перегрузки ввода/вывода
	friend fstream& operator<<(fstream& out, Bank& obj);
	friend fstream& operator>>(fstream& in, Bank& obj);
};

