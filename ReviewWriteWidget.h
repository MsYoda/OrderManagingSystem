#pragma once

#include <QWidget>
#include "ui_ReviewWriteWidget.h"
#include "CheckFunctions.h"
#include "Review.h"
#include "Assortment.h"

class ReviewWriteWidget : public QWidget
{
	Q_OBJECT
	Review* review;		// Указатель на новый отзыв

public:
	ReviewWriteWidget(QWidget *parent = nullptr);	// Конструктор
	~ReviewWriteWidget();	// Деструктор

	void SetProductID(int id);	// Установить id товара
	void SetUserName(QString username);	// Установить имя пользователя

public slots:
	void SaveButtonClicked();	// Сохранить отзыв

signals:
	void ReviewCreated(Review* review);	// Отзыв был создан
private:
	Ui::ReviewWriteWidgetClass ui; // Доступ к элементам из редактора
};
