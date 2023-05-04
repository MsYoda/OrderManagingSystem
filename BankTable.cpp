#include "BankTable.h"

// Конструктор
BankTable::BankTable(QWidget* parent) :BaseTable(parent)
{
	bank = nullptr;
}

// Установить поля таблицы
void BankTable::SetupTable(Bank* bank)
{
	this->bank = bank;
}

// Обновить таблицу
void BankTable::UpdateTable()
{
	this->setRowCount(0);
	int sumAfterTransaction = bank->GetCash();
	std::vector<Transaction>::iterator it = bank->GetTransactionsEnd();
	// Вывод идёт с конца вектора, так как в конец добавляются самые новые операции
	for (unsigned int i = 0; it != bank->GetTransactionsBegin(); i++)
	{
		--it;
		this->insertRow(i);
		Transaction transaction = *it;
		this->setItem(i, 0, new QTableWidgetItem(transaction.sender));
		this->setItem(i, 1, new QTableWidgetItem(transaction.receiver));
		this->setItem(i, 2, new QTableWidgetItem(QString::number(transaction.sum)));
		this->setItem(i, 3, new QTableWidgetItem(QString::number(sumAfterTransaction)));
		sumAfterTransaction -= transaction.sum;
	}
	this->parentWidget()->findChild<QLabel*>("balance_label")->setText(QString::number(bank->GetCash()) + "$");
}
