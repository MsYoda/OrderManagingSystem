#include "ReviewWriteWidget.h"
#include "InputExeption.h"

// Конструктор
ReviewWriteWidget::ReviewWriteWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.close_button, &QPushButton::clicked, this, [=]() {this->deleteLater(); });
	connect(ui.save_button, &QPushButton::clicked, this, &ReviewWriteWidget::SaveButtonClicked);

	this->review = new Review;

	connect(this, SIGNAL(ReviewCreated(Review*)), this->parentWidget(), SLOT(AddNewReview(Review*)));
}

// Деструктор
ReviewWriteWidget::~ReviewWriteWidget()
{
	delete this->review;
}
// Установить id товара
void ReviewWriteWidget::SetProductID(int id)
{
	this->review->SetProductID(id);
	ui.product_name_label->setText(Assortment::GetByID(id)->GetName());
}
// Установить имя пользовател
void ReviewWriteWidget::SetUserName(QString username)
{
	this->review->SetUsername(username);
}
// Сохранить отзыв
void ReviewWriteWidget::SaveButtonClicked()
{
	this->review->SetText(ui.review_text->toPlainText());
	try
	{
		// Проверка, что оценка введена в грницах от 1 до 5
		CheckInt(ui.rating_box->value(), 1, 5);
		if (this->review->GetText().length() < 1) throw InputExeption("При вводе текста допущена ошибка! Не введено ни одного символа!");
	}
	catch (InputExeption excep)
	{
		QString text = "При вводе оценки ";
		excep.Show(ui.error_label, &text);
		return;
	}
	this->review->SetMark(ui.rating_box->value());
	emit ReviewCreated(review);
	this->deleteLater();
}