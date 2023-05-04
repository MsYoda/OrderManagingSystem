#include "BaseProductTable.h"
#include "EditMenu.h"

// Установить фильтр
void BaseProductTable::SetFilter(Product* newFilterLeft, Product* newFilterRight)
{
	this->leftFilterBorder = newFilterLeft;
	this->rightFilterBorder = newFilterRight;

	this->CreateFilterMenu();
}

// Редактировать фильтр
void BaseProductTable::EditFilter()
{
	if (this->leftFilterBorder && this->rightFilterBorder)
	{
		this->CreateFilterMenu();
	}
}

// Установить виджет главного окна
void BaseProductTable::SetMainWidget(QWidget* parent)
{
	this->mainWindow = parent;
}

// Создать меню фильтра
void BaseProductTable::CreateFilterMenu()
{
	// Создание 2 EditMnu для левой и правой грацниы фильтра
	QWidget* leftMenu = this->leftFilterBorder->OpenEditMenu('f', this->parentWidget()->parentWidget()->parentWidget()->parentWidget());
	leftMenu->setGeometry(10, leftMenu->y(), leftMenu->width(), leftMenu->height());
	leftMenu->setObjectName("left_filter");
	dynamic_cast<EditMenu*>(leftMenu)->SetTitle("Редактирование левой границы поиска");

	QWidget* rightMenu = this->rightFilterBorder->OpenEditMenu('f', this->parentWidget()->parentWidget()->parentWidget()->parentWidget(), true);
	rightMenu->setGeometry(leftMenu->x() + leftMenu->width() + 5, leftMenu->y(), rightMenu->width(), rightMenu->height());
	rightMenu->setObjectName("right_filter");
	dynamic_cast<EditMenu*>(rightMenu)->SetTitle("Редактирование правой границы поиска");
}

// Добавить строку в таблицу
void BaseProductTable::AddString(int i, Product* obj)
{
	this->insertRow(i);
	QTableWidgetItem* item = new QTableWidgetItem(obj->GetTypeName());
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	this->setItem(i, 0, item);

	item = new QTableWidgetItem((obj->GetName()));
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	this->setItem(i, 1, item);

	item = new QTableWidgetItem;
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	item->setData(Qt::EditRole, obj->GetCost());
	this->setItem(i, 2, item);

	item = new QTableWidgetItem("");
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	this->setItem(i, 3, item);

	item = new QTableWidgetItem;
	item->setData(Qt::EditRole, obj->GetID());
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	this->setItem(i, 4, item);
}

// Обновить таблицу
void BaseProductTable::UpdateTable()
{
	this->setRowCount(0);
	BinaryTree<Product*>::Iterator it = Assortment::assortment.Begin();
	for (int i = 0; it != Assortment::assortment.End(); it++, i++)
	{
		// Если есть фильтр, то выводим только то, что подходит под него
		if (this->leftFilterBorder && this->rightFilterBorder)
		{
			if (this->leftFilterBorder->GetFilterComparator()->operator()(leftFilterBorder, *it, rightFilterBorder))
			{
				this->AddString(i, *it);
			}
			else i--;
		}
		// Иначе выводим всё
		else
		{
			this->AddString(i, *it);
		}
	}
}

// Создать виджет с описанием товара
void BaseProductTable::OpenDescription(const QModelIndex& index)
{
	if (descriptionWidget) return;

	descriptionWidget = new QDialog(this);
	descriptionWidget->setGeometry(QCursor::pos().x(), QCursor::pos().y(), 300, 300);
	QFrame* frame = new QFrame(descriptionWidget);
	frame->setGeometry(0, 0, 300, 300);
	frame->setAutoFillBackground(true);
	frame->setFrameShape(QFrame::Box);
	frame->setFrameShadow(QFrame::Raised);
	frame->setLineWidth(2);

	QLabel* title = new QLabel(frame);
	QFont font = title->font();
	font.setPixelSize(15);
	title->setFont(font);
	title->setText("Характеристики товара");
	title->setGeometry(10, 10, 300, 15);

	int id = this->item(this->currentRow(), 4)->text().toInt();
	QLabel* descriptionLabel = new QLabel(frame);
	font = descriptionLabel->font();
	font.setPixelSize(15);
	descriptionLabel->setFont(font);

	descriptionLabel->setGeometry(10, 35, 300, 300);
	descriptionLabel->setAlignment(Qt::AlignTop);

	QString description = Assortment::GetByID(id)->GenerateDescription();
	descriptionLabel->setText(description);

	QPushButton* closeBut = new QPushButton(frame);
	closeBut->setText("Закрыть");
	closeBut->setGeometry(70, 270, 140, 25);
	connect(closeBut, &QPushButton::clicked, this, [=]()
		{
			this->descriptionWidget->deleteLater();
			this->descriptionWidget = nullptr;
		});
	descriptionWidget->show();
}

// Сортировать по возрастанию цены
void BaseProductTable::slotSortByRising()
{
	this->sortByColumn(2, Qt::SortOrder::AscendingOrder);
}

// Сортировать по убыванию цены
void BaseProductTable::slotSortByDecreasing()
{
	this->sortByColumn(2, Qt::SortOrder::DescendingOrder);
}

// Создать меню сортировки
void BaseProductTable::CreateMenu(QMenu* menu)
{
	menu->addSeparator();
	QAction* action = menu->addAction("Сортировать по возрастанию цены");
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(slotSortByRising()));

	action = menu->addAction("Сортировать по убыванию цены");
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(slotSortByDecreasing()));
}

// Удалить фильтр
void BaseProductTable::DeleteFilter()
{
	if (this->leftFilterBorder && this->rightFilterBorder)
	{
		delete this->leftFilterBorder;
		delete this->rightFilterBorder;

		this->leftFilterBorder = nullptr;
		this->rightFilterBorder = nullptr;

		this->UpdateTable();
	}
}

// Конструктор
BaseProductTable::BaseProductTable(QWidget* parent) : BaseTable(parent)
{
	this->mainWindow = nullptr;
	this->setFocusPolicy(Qt::NoFocus);
	QObject::connect(this, SIGNAL(doubleClicked(const QModelIndex&)), SLOT(OpenDescription(const QModelIndex&)));
}

// Декструктор
BaseProductTable::~BaseProductTable()
{
	if (descriptionWidget) delete descriptionWidget;
	delete leftFilterBorder;
	delete rightFilterBorder;
}
