#include "OrderSystem.h"
#include "Assortment.h"

#include "EditMenu.h"
#include "ProductTable.h"
#include "InputExeption.h"
#include "algorithm.cpp"

#define ADMIN_ACCOUNT_NAME "admin"

// Конструктор
OrderSystem::OrderSystem(QWidget *parent) : QMainWindow(parent)
{
	this->SetupFiles();
	ui.setupUi(this);
	ui.stackedWidget->setCurrentIndex(2);

	ui.signIn_errorLabel->setStyleSheet("color: rgb(255, 0, 0)");
	ui.errorLogin_label->setStyleSheet("color: rgb(255, 0, 0)");

	// Настройка парметров таблиц
	ui.backet_table->setColumnWidth(0, 150);
	ui.admin_order_table->setColumnWidth(4, 100);

	// Настройка меню кнопки "Добавить товар"
	//=========================

	QMenu* menu = new QMenu(this);

	QAction* newFilterAct = menu->addAction("Добавить процессор");
	connect(newFilterAct, &QAction::triggered, this, [=]() {OpenEditMenu(new CPU, 'c'); });

	newFilterAct = menu->addAction("Добавить видеокарту");
	connect(newFilterAct, &QAction::triggered, this, [=]() {OpenEditMenu(new GPU, 'c'); });

	newFilterAct = menu->addAction("Добавить хололильник");
	connect(newFilterAct, &QAction::triggered, this, [=]() {OpenEditMenu(new Fridge, 'c'); });

	newFilterAct = menu->addAction("Добавить стиральную машину");
	connect(newFilterAct, &QAction::triggered, this, [=]() {OpenEditMenu(new Washmachine, 'c'); });

	newFilterAct = menu->addAction("Добавить клавиатуру");
	connect(newFilterAct, &QAction::triggered, this, [=]() {OpenEditMenu(new Keyboard, 'c'); });

	newFilterAct = menu->addAction("Добавить мышку");
	connect(newFilterAct, &QAction::triggered, this, [=]() {OpenEditMenu(new Mouse, 'c'); });

	ui.add_product_button->setMenu(menu);
	ui.add_product_button->setPopupMode(QToolButton::InstantPopup);
	//===================

	// Настройка кнопок фильтра
	this->SetupFilterButton(ui.filter_button, ui.admin_product_table);
	this->SetupFilterButton(ui.filter_button_user, ui.user_product_table);
	
	// Настройка основных сигналов и слотов
	connect(ui.form_order, SIGNAL(clicked()), ui.backet_table, SLOT(CreateOrder()));

	connect(ui.user_tab_widget, SIGNAL(tabBarClicked(int)), this, SLOT(shouldUpdateTable(int)));
	connect(ui.admin_tab_widget, SIGNAL(tabBarClicked(int)), this, SLOT(shouldUpdateAdminTables(int)));

	connect(ui.backet_table, SIGNAL(orderCreated(Order*)), this, SLOT(AddNewOrder(Order*)));

	connect(ui.signIn_back, SIGNAL(clicked()), this, SLOT(CreateUserBackButtonClicked()));
	connect(ui.reg_button, SIGNAL(clicked()), this, SLOT(RegButtonClicked()));
	connect(ui.signin_register_button, SIGNAL(clicked()), this, SLOT(CreateUserButtonClicked()));
	connect(ui.signin_button, SIGNAL(clicked()), this, SLOT(SignInButtonClicked()));
	connect(ui.exit_to_register_menu, SIGNAL(clicked()), this, SLOT(ExitToRegisterMenu())); 
	connect(ui.exit_to_register_menu_admin, SIGNAL(clicked()), this, SLOT(ExitToRegisterMenu()));


	connect(ui.user_order_table, SIGNAL(userDenieOrder(QString)), SLOT(DecreaseRating(QString)));
	connect(ui.admin_order_table, SIGNAL(orderAccepted(QString)), SLOT(IncreaseRating(QString)));
	
	// Настройка таблицы с товарами для администратора
	ui.admin_product_table->SetMainWidget(this);
	ui.admin_product_table->SetupUndoStack();
	ui.admin_product_table->setColumnWidth(0, 150);
	//ui.admin_product_table->hideColumn(3);
	//ui.admin_product_table->hideColumn(4);
	connect(ui.admin_product_table, SIGNAL(openWatchReviewMenu(int)), SLOT(CreateWatchReviewMenu(int)));

	// Настройка таблицы с товарами для пользователя
	ui.user_product_table->setColumnWidth(0, 150);
	//ui.user_product_table->hideColumn(3);
	//ui.user_product_table->hideColumn(4);
	connect(ui.user_product_table, SIGNAL(openReviewMenu(int)), SLOT(CreateReviewMenu(int)));
	connect(ui.user_product_table, SIGNAL(openWatchReviewMenu(int)), SLOT(CreateWatchReviewMenu(int)));
	connect(ui.user_product_table, SIGNAL(addedItemToBacket(int)), ui.backet_table, SLOT(AddToBacket(int)));

	// Загрузка данных из файлов
	this->LoadUsersFromFile();
	this->LoadReviewsFromFile(); 

	OrdersCollector::ReadOrdersFromFile(this->ordersFile);

	this->LoadBank();

	Assortment::LoadAssortmentFromFile<CPU>(cpuFile);
	Assortment::LoadAssortmentFromFile<GPU>(gpuFile);
	Assortment::LoadAssortmentFromFile<Fridge>(fridgeFile);
	Assortment::LoadAssortmentFromFile<Washmachine>(washmachineFile);
	Assortment::LoadAssortmentFromFile<Mouse>(mouseFile);
	Assortment::LoadAssortmentFromFile<Keyboard>(keyboardFile);

	// Обновление таблиц с информацией
	ui.bank_table->SetupTable(&this->bank);
	ui.admin_order_table->SetupTable(&this->registredUsers, &this->bank);

	this->setFixedSize(this->size());

	connect(ui.save_allinfo_button, SIGNAL(clicked()), this, SLOT(SaveAllInfoInFile()));
	connect(ui.save_allinfo_button_1, SIGNAL(clicked()), this, SLOT(SaveAllInfoInFile()));
}

// Настроить кнопку открытия фильтра
void OrderSystem::SetupFilterButton(QToolButton* button, BaseProductTable* table)
{
	QMenu* menu = new QMenu(this);
	QAction* action;
	action = menu->addAction("Создать новый фильтр");
	QMenu* newFilterMenu= new QMenu(this);
	QAction* newFilterAct;

	newFilterAct = newFilterMenu->addAction("Процессор");
	connect(newFilterAct, &QAction::triggered, this, [=]() {table->SetFilter(new CPU, new CPU); });

	newFilterAct = newFilterMenu->addAction("Видеокарта");
	connect(newFilterAct, &QAction::triggered, this, [=]() {table->SetFilter(new GPU, new GPU); });

	newFilterAct = newFilterMenu->addAction("Холодильник");
	connect(newFilterAct, &QAction::triggered, this, [=]() {table->SetFilter(new Fridge, new Fridge); });

	newFilterAct = newFilterMenu->addAction("Стиральная машина");
	connect(newFilterAct, &QAction::triggered, this, [=]() {table->SetFilter(new Washmachine, new Washmachine); });

	newFilterAct = newFilterMenu->addAction("Клавиатура");
	connect(newFilterAct, &QAction::triggered, this, [=]() {table->SetFilter(new Keyboard, new Keyboard); });

	newFilterAct = newFilterMenu->addAction("Мышь");
	connect(newFilterAct, &QAction::triggered, this, [=]() {table->SetFilter(new Mouse, new Mouse); });

	action->setMenu(newFilterMenu);

	action = menu->addAction("Редактировать текущий фильтр");
	connect(action, &QAction::triggered, this, [=]() {table->EditFilter(); });

	action = menu->addAction("Очистить фильтр");
	connect(action, &QAction::triggered, this, [=]() {table->DeleteFilter(); });
  

	button->setMenu(menu);
	button->setPopupMode(QToolButton::InstantPopup);
}

// Настройка файлов
void OrderSystem::SetupFiles()
{
	cpuFile.SetFileName("data//cpu.bin");
	gpuFile.SetFileName("data//gpu.bin");
	fridgeFile.SetFileName("data//fridge.bin");
	washmachineFile.SetFileName("data//washmachine.bin");
	mouseFile.SetFileName("data//mouse.bin");
	keyboardFile.SetFileName("data//keyboard.bin");
	ordersFile.SetFileName("data//orders.bin");
	reviewsFile.SetFileName("data//reviews.bin");
	userFile.SetFileName("data//users.bin");
	bankFile.SetFileName("data//bank.bin");
}

// Сохранение ассортимента в файлы
void OrderSystem::SaveAssortmentToFiles()
{
	cpuFile.OpenForWriting();
	gpuFile.OpenForWriting();
	fridgeFile.OpenForWriting();
	washmachineFile.OpenForWriting();
	mouseFile.OpenForWriting();
	keyboardFile.OpenForWriting();

	BinaryTree<Product*>::Iterator it = Assortment::assortment.Begin();
	for (; it != Assortment::assortment.End(); it++)
	{
		// Определение типа элемента в контейнере
		if      (cpuFile.IsOpen() && dynamic_cast<CPU*>(*it))					cpuFile.WriteObj(dynamic_cast<CPU*>(*it));
		else if (gpuFile.IsOpen() && dynamic_cast<GPU*>(*it))					gpuFile.WriteObj(dynamic_cast<GPU*>(*it));
		else if (fridgeFile.IsOpen() && dynamic_cast<Fridge*>(*it))				fridgeFile.WriteObj(dynamic_cast<Fridge*>(*it));
		else if (washmachineFile.IsOpen() && dynamic_cast<Washmachine*>(*it))   washmachineFile.WriteObj(dynamic_cast<Washmachine*>(*it));
		else if (mouseFile.IsOpen() && dynamic_cast<Mouse*>(*it))				mouseFile.WriteObj(dynamic_cast<Mouse*>(*it));
		else if (keyboardFile.IsOpen() && dynamic_cast<Keyboard*>(*it))			keyboardFile.WriteObj(dynamic_cast<Keyboard*>(*it));
	}
	cpuFile.Close();
	gpuFile.Close();
	fridgeFile.Close();
	washmachineFile.Close();
	mouseFile.Close();
	keyboardFile.Close();
}

// Сохранение пользователей в файл
void OrderSystem::SaveUsersToFile()
{
	this->userFile.OpenForWriting();
	if (this->userFile.IsOpen())
	{
		for (BinaryTree<User>::Iterator it = this->registredUsers.Begin(); it != this->registredUsers.End(); it++)
		{
			User* obj = &(*it);
			this->userFile.WriteObj(obj);
		}
		this->userFile.Close();
	}
}

// Загрузка пользователей из файла
void OrderSystem::LoadUsersFromFile()
{
	this->userFile.OpenForReading();
	if (this->userFile.IsOpen())
	{
		while (!this->userFile.IsEndOfFile())
		{
			User loadUser;
			loadUser = this->userFile.ReadObj();
			if (!loadUser.IsEmpty()) this->registredUsers.AddData(loadUser);
		}

		this->userFile.Close();
	}
}

// Сохранение отзывов в файл
void OrderSystem::SaveReviewsToFile()
{
	this->reviewsFile.OpenForWriting();
	if (this->reviewsFile.IsOpen())
	{
		for (BinaryTree<Review>::Iterator it = this->reviews.Begin(); it != this->reviews.End(); it++)
		{
			Review* obj = &(*it);
			this->reviewsFile.WriteObj(obj);
		}
		this->reviewsFile.Close();
	}
}

// Загрузка отзывов из файла
void OrderSystem::LoadReviewsFromFile()
{
	this->reviewsFile.OpenForReading();
	Review review;
	if (this->reviewsFile.IsOpen())
	{
		while (!this->reviewsFile.IsEndOfFile())
		{
			review = this->reviewsFile.ReadObj();
			if (this->reviewsFile.IsEndOfFile())
			{
				break;
			}
			this->reviews.AddData(review);
		}
		this->reviewsFile.Close();
	}
}

// Сохранить банк в файл
void OrderSystem::SaveBank()
{
	bankFile.OpenForWriting();
	if (this->bankFile.IsOpen())
	{
		bankFile.WriteObj(&this->bank);
		bankFile.Close();
	}
}

// Загрузка банка из файла
void OrderSystem::LoadBank()
{
	bankFile.OpenForReading();
	if (this->bankFile.IsOpen())
	{
		this->bank = bankFile.ReadObj();
		bankFile.Close();
	}
}
// Сохранить всю информацию в файлы
void OrderSystem::SaveAllInfoInFile()
{
	this->SaveAssortmentToFiles();
	this->SaveReviewsToFile();
	OrdersCollector::WriteOrdersToFile(this->ordersFile);
	this->SaveUsersToFile();
	this->SaveBank();
}

// Проверка нужно ли обновлять клиентские таблицы
void OrderSystem::shouldUpdateTable(int ind)
{
	if (ui.user_tab_widget->tabText(ind) == "Корзина")
	{
		ui.backet_table->UpdateTable();
		ui.create_order_error_label->setText(" ");
	}
	else if (ui.user_tab_widget->tabText(ind) == "Заказы")
	{
		ui.user_order_table->UpdateTable();
	}
}
// Проверка нужно ли обновлять таблицы админстратора
void OrderSystem::shouldUpdateAdminTables(int ind)
{
	if (ui.admin_tab_widget->tabText(ind) == "Заказы")
	{
		ui.admin_order_table->UpdateTable();
	}
	else if (ui.admin_tab_widget->tabText(ind) == "Бухгалтерия")
	{
		ui.bank_table->UpdateTable();
	}
}

void OrderSystem::RememberAction(Product* obj, char action)
{

}
// Добавить заказ в контейнер
void OrderSystem::AddNewOrder(Order* order)
{
	order->SetUsername(this->currentUser.GetUserName());
	OrdersCollector::orders.AddData(order);

	Transaction transaction = Transaction(order->GetUsername(), ADMIN_ACCOUNT_NAME, order->GetSum());
	this->bank.AddTransaction(transaction);
}

// Уменьшить рейтинг пользователю
void OrderSystem::DecreaseRating(QString username)
{
	for (BinaryTree<User>::Iterator it = this->registredUsers.Begin(); it != this->registredUsers.End(); it++)
	{
		if ((*it).GetUserName() == username)
		{
			(*it).SetRating((*it).GetRating() - 2);
			break;
		}
	}
}

// Кнопка "зарегистрироваться" нажата
void OrderSystem::RegButtonClicked() { ui.stackedWidget->setCurrentIndex(1); }
// Кнопка вернуться в меню логина нажата
void OrderSystem::CreateUserBackButtonClicked() { ui.stackedWidget->setCurrentIndex(2); }
// Кнопка "Выйти из аккаунта" нажата
void OrderSystem::ExitToRegisterMenu() 
{
	ui.stackedWidget->setCurrentIndex(2);
	auto childenList = this->findChildren<EditMenu*>();
	for (auto it = childenList.begin(); it != childenList.end(); it++)
		(*it)->deleteLater();
};

// Кнопка регистрации нажата
void OrderSystem::CreateUserButtonClicked()
{
	User newUser;
	newUser.SetUserName(ui.singIn_login->text());
	try
	{
		if (ui.singIn_password->text() == ADMIN_ACCOUNT_NAME && ui.singIn_login->text() == ADMIN_ACCOUNT_NAME)
			throw InputExeption("Ошибка! Пользователь с таким именем уже зарегистрирован!");

		// Проверка считанного имени пользователя
		if (ui.singIn_password->text() != ui.signIn_checkPassword->text()) throw InputExeption("Ошибка! Пароли не совпадают!");
		if (ui.singIn_password->text().length() == 0) throw InputExeption("Ошибка! Вы не ввели в поле пароля ни одного символа!");
		if (ui.singIn_login->text().length() == 0) throw InputExeption("Ошибка! Вы не ввели в поле логина ни одного символа!");

		// Проверка не дублируется ли введённое имя пользователя
		container::for_each(this->registredUsers.Begin(), this->registredUsers.End(), [&](User& user)
			{
				if(user.GetUserName() == newUser.GetUserName()) throw InputExeption("Ошибка! Пользователь с таким именем уже зарегистрирован!");
			});
	}
	catch(InputExeption excep)
	{
		excep.Show(ui.signIn_errorLabel);
		return;
	}
	
	ui.signIn_errorLabel->setText("");
	newUser.SetPassword(ui.singIn_password->text());
	this->registredUsers.AddData(newUser);
	ui.stackedWidget->setCurrentIndex(2);
}

// Кнопка входа в систему нажата
void OrderSystem::SignInButtonClicked()
{
	ui.admin_product_table->UpdateTable();
	ui.user_product_table->UpdateTable();

	// Отдельный вход для администратора
	if (ui.loginText->text() == ADMIN_ACCOUNT_NAME && ui.passwordText->text() == ADMIN_ACCOUNT_NAME)
	{
		ui.stackedWidget->setCurrentIndex(3);
		return;
	}

	User userToLogin;
	userToLogin.SetUserName(ui.loginText->text());
	userToLogin.SetPassword(ui.passwordText->text());
	User* findedUser;

	try
	{
		// Поиск пользователя по введённым данным
		auto findedUserIter = container::find_if(registredUsers.Begin(), registredUsers.End(), [&](User obj) { return obj == userToLogin; });
		if (findedUserIter != registredUsers.End())
		{
			// Если пользователь найден, то вход переход в интерфейс пользователя
			User findedUser = *findedUserIter;
			this->currentUser = findedUser;
			ui.user_order_table->SetupTable(this->currentUser.GetUserName(), &this->bank);
			ui.user_order_table->UpdateTable();
			ui.backet_table->ClearTable();

			ui.stackedWidget->setCurrentIndex(0);
			ui.userName_label->setText(this->currentUser.GetUserName());
			ui.enter_error_label->setText("");
		}
		else throw InputExeption("Не найден аккаунт со введёными данными! Проверьте правильность ввода логина или пароля!");
	}
	catch (InputExeption excep)
	{
		excep.Show(ui.enter_error_label);
	}
	ui.enter_error_label->setText("");
}

// Открыть меню редактирования товара
void OrderSystem::OpenEditMenu(Product* obj, char modeFlag)
{
	if (!(this->findChild<EditMenu*>()))
		obj->OpenEditMenu(modeFlag, this);
}

// Добавить новвый отзыв в контейнер
void OrderSystem::AddNewReview(Review* review)
{
	this->reviews.AddData(*review);
}

// Создать меню написания отзывов
void OrderSystem::CreateReviewMenu(int id)
{
	ReviewWriteWidget* menu = new ReviewWriteWidget(this);
	menu->SetProductID(id);
	menu->SetUserName(this->currentUser.GetUserName());
	menu->setGeometry(20, 50, menu->width(), menu->height());
	menu->show();
}

// Создать меню просмотра отзывов
void OrderSystem::CreateWatchReviewMenu(int id)
{
	ReviewsMenu* menu = new ReviewsMenu(this);
	menu->SetProductID(id);
	menu->SetReviewsTree(&reviews);
	menu->SetUsersTree(&registredUsers);
	menu->UpdateTable();
	menu->setGeometry(20, 50, menu->width(), menu->height());
	menu->show();
}

// Деструктор
OrderSystem::~OrderSystem()
{
	// Сохранение всей информации в файлы
	SaveAllInfoInFile();

	// Очитска дополнительной памяти, выделенной в контейнерах
	container::for_each(OrdersCollector::orders.Begin(), OrdersCollector::orders.End(), [](Order* obj) {delete obj; });
	container::for_each(Assortment::assortment.Begin(), Assortment::assortment.End(), [](Product* obj) {delete obj; });
  
}
