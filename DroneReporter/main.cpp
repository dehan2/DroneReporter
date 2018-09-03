#include "DroneReporter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DroneReporter w;
	w.show();
	return a.exec();
}
