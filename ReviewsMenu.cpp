#include "ReviewsMenu.h"
#include "qdialog.h"

// Конструктор
ReviewsMenu::ReviewsMenu(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->productID = 0;
	this->reviews = nullptr;
	this->users = nullptr;

	// Настройка обработки основных сигналов
	QObject::connect(ui.close_button, &QPushButton::clicked, this, [=]() {
		this->deleteLater(); });
	QObject::connect(ui.review_table, SIGNAL(doubleClicked(const QModelIndex&)), SLOT(OpenReviewText(const QModelIndex&)));

	// Генерация окна с текстом отзыва
	QDialog* reviewWidget = new QDialog(this);
	reviewWidget->setObjectName("text_of_review");
	reviewWidget->setGeometry(QCursor::pos().x(), QCursor::pos().y(), 700, 300);
	QFrame* frame = new QFrame(reviewWidget);
	frame->setGeometry(0, 0, 700, 300);
	frame->setAutoFillBackground(true);
	frame->setFrameShape(QFrame::Box);
	frame->setFrameShadow(QFrame::Raised);
	frame->setLineWidth(1);

	QLabel* title = new QLabel(frame);
	QFont font = title->font();
	font.setPixelSize(15);
	title->setFont(font);
	title->setText("Текст отзыва");
	title->setGeometry(10, 10, 300, 15);

	QTextBrowser* descriptionLabel = new QTextBrowser(frame);
	descriptionLabel->setObjectName("review_text");
	descriptionLabel->setGeometry(10, 35, 600, 200);;

	QPushButton* closeBut = new QPushButton(frame);
	closeBut->setText("Закрыть");
	closeBut->setGeometry(10, 270, 140, 25);

	// Кнопка закрытия меню с текстом отзыва
	connect(closeBut, &QPushButton::clicked, this, [=]()
		{
			this->findChild<QWidget*>("text_of_review")->hide();//
		});
	reviewWidget->hide();
}

// Установить ID товара 
void ReviewsMenu::SetProductID(int id)
{
	this->productID = id;
}
// Установить указатель на отзывы
void ReviewsMenu::SetReviewsTree(BinaryTree<Review>* reviews)
{
	this->reviews = reviews;
}
// Установить указатель на пользоватлей
void ReviewsMenu::SetUsersTree(BinaryTree<User>* users)
{
	this->users = users;
}
// Обновить таблицу
void ReviewsMenu::UpdateTable()
{
	BinaryTree<Review>::Iterator it = reviews->Begin();
	for (int i = 0; it != reviews->End(); i++, it++)
	{
		// Вывод только отзывов на выбранный товар
		if ((*it).GetProductID() == this->productID)
		{
			User user;
			// Поиск информации о авторе отзыва
			for (BinaryTree<User>::Iterator userIt = users->Begin(); userIt != users->End(); userIt++)
			{
				if ((*it).GetUsername() == (*userIt).GetUserName()) user = (*userIt);
			}

			// Заполнение строки таблицы
			ui.review_table->insertRow(i);
			ui.review_table->setItem(i, 0, new QTableWidgetItem(user.GetUserName()));
			ui.review_table->setItem(i, 1, new QTableWidgetItem(QString::number(user.GetRating())));
			ui.review_table->setItem(i, 2, new QTableWidgetItem(QString::number((*it).GetMark())));
			ui.review_table->setItem(i, 3, new QTableWidgetItem((*it).GetText()));
		}
		else i--;
	}
	ui.review_table->hideColumn(3);
}

// Открыть меню просмотра текста отзыва
void ReviewsMenu::OpenReviewText(const QModelIndex&)
{
	if (this->findChild<QWidget*>("text_of_review"))
	{
		QString text = ui.review_table->item(ui.review_table->currentRow(), 3)->text();
		this->findChild<QWidget*>("text_of_review")->findChild<QTextBrowser*>("review_text")->setText(text);
		this->findChild<QWidget*>("text_of_review")->show();
	}
}
