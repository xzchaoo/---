#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	MainWindow mainWindow;
	//窗口最大化
	mainWindow.setWindowState (Qt::WindowMaximized);
	mainWindow.show ();
	return app.exec();
}
