#include "OrderSystem.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OrderSystem w;
	w.show();
	return a.exec();
}
