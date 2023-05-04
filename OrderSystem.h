#pragma once

#include <QtWidgets/QMainWindow>
#include <qmenu.h>
#include "ui_OrderSystem.h"

#include "User.h"
#include "Products.h"
#include "CPUEditMenu.h"

#include "templates//BinaryTree.cpp"
#include "templates/Comparator.h"
#include <vector>

#include "BinaryFile.cpp"
#include "OrdersCollector.h"

#include "Review.h"
#include "ReviewWriteWidget.h"
#include "ReviewsMenu.h"

#include "Bank.h"

class OrderSystem : public QMainWindow
{
	Q_OBJECT

private:
	Ui::OrderSystemClass ui; // Доступ к виджетам из редактора

	User currentUser;  // Теекущий пользователь
	BinaryTree<User> registredUsers; // контейнер с зарегистрованными пользователями
	BinaryTree<Review> reviews; // контейнер с отзывами

	BinaryFile<CPU> cpuFile;    // файл с процессорами
	BinaryFile<GPU> gpuFile;    // файл с видеокартами
	BinaryFile<Fridge> fridgeFile;  // файл с холодильниками
	BinaryFile<Washmachine> washmachineFile;    // файл со стиральными машинами
	BinaryFile<Mouse> mouseFile;    // файл с мышками
	BinaryFile<Keyboard> keyboardFile;  // файл с клавиатурами

	BinaryFile<Order> ordersFile;   // файл с заказами
	BinaryFile<Review> reviewsFile; // файл с отзывами
	BinaryFile<User> userFile;      // файл с пользователями

	BinaryFile<Bank> bankFile;      // файл с банком

	Bank bank;  // Банк

	// Настроить кнопку открытия фильтра
	void SetupFilterButton(QToolButton* button, BaseProductTable* table);
	void SetupFiles();  // Настроить файлы

	void SaveAssortmentToFiles();   // Сохранить ассортимент в файл

	void SaveUsersToFile(); // СОхранить пользователей в файл
	void LoadUsersFromFile();   // Загрузить пользователей из файла

	void SaveReviewsToFile();   // Сохранить отзывы в файл
	void LoadReviewsFromFile(); // Загрузить отзывы из файла

	void SaveBank();    // Сохранить банк
	void LoadBank();    // Загрузить банк


public slots:

	void RegButtonClicked();    // Кнопка "зарегистрироваться" нажата
	void CreateUserBackButtonClicked(); // Кнопка вернуться в меню логина нажата
	void CreateUserButtonClicked();     // Кнопка регистрации нажата
	void SignInButtonClicked();     // Кнопка входа в систему нажата
	void ExitToRegisterMenu();      // Кнопка "Выйти из аккаунта" нажата

	void shouldUpdateTable(int ind);    // Проверка нужно ли обновлять клиентские таблицы
	void shouldUpdateAdminTables(int ind);  // Проверка нужно ли обновлять таблицы админстратора
	void RememberAction(Product* obj, char action); // Запомнить последнее действие
	void AddNewOrder(Order* order);     // Добавить заказ в контейнер

	void DecreaseRating(QString username);  // Уменьшить рейтинг пользователю

	void OpenEditMenu(Product* cpu, char modeFlag); // Открыть меню редактирования
	  
	void AddNewReview(Review* review);  // Добавить отзыв в контейнер
	void CreateReviewMenu(int id);      // Создать меню написания отзывов

	void CreateWatchReviewMenu(int id); // Создать меню просмотра отзывов
	void SaveAllInfoInFile();			// Сохранить всю информацию в файлы

public:

	OrderSystem(QWidget *parent = nullptr); // Конструктор
	~OrderSystem();                         // Деструктор

};
