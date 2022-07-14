#include "MyWindow.h"
#include <iostream>
int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	MyWindow w(argc, argv);
	w.show();

	return a.exec();
}