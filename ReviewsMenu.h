#pragma once

#include <QWidget>
#include "ui_ReviewsMenu.h"
#include "templates//BinaryTree.cpp"
#include "Review.h"
#include "qtextbrowser.h"

class ReviewsMenu : public QWidget
{
	Q_OBJECT
	BinaryTree<Review>* reviews; // Указатель на контейнер с отзывами
	BinaryTree<User>* users;	// Указатель на контейнер с пользователями
	int productID;				// ID товара

public slots:
	void OpenReviewText(const QModelIndex& ind);	// Открыть меню просмотра текста отзыва
public:
	ReviewsMenu(QWidget *parent = nullptr);	// Конструктор

	void SetProductID(int id);		// Установить ID товара
	void SetReviewsTree(BinaryTree<Review>* reviews);	// Установить указатель на отзывы
	void SetUsersTree(BinaryTree<User>* users);			// Установить указатель на пользоватлей

	void UpdateTable();		// Обновить таблицу

private:
	Ui::ReviewsMenuClass ui;	// Доступ к элементам из редактора
};
