#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include "CodeEditor.h"
#include "Editor.h"
#include "omnithread.h"
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <iostream>
#include <utility>

class MyWindow : public QMainWindow {
	Q_OBJECT
public:

	MyWindow(int argc, char** argv, QWidget* parent = NULL);

	//������ �������������
	void init();					//����� ����� �������������
	void initActions();				//������������� ��������
	void initMainMenu();			//������������� ����
	void initToolBars();			//������������� ��������
	void initStatusBar();			//������������� ��������� ������
	void initCentralWidget();		//������������� ������������ �������
	void initConsoleDock();			//������������� �������
	void initThread();				//������������� ������
	//�����
public slots:
	void slotSaveAs();
	void slotClear();
	void slotRun();
	void slotSave();
	void slotAbout();
	void textChanged(const QString&);
protected:
	int _argc;
	char** _argv;

private:
	QPointer<QMenu> mSend;
	QPointer<QMenu> mFile;
	QPointer<QMenu> mHelp;

	QPointer<QAction> aAbout;
	QPointer<QAction> aSave;
	QPointer<QAction> aSaveAs;
	QPointer<QAction> aExit;
	QPointer<QAction> aClear;
	QPointer<QAction> aRun;
	QPointer<QToolBar> toolbar;
	QString filename;
	

	QPointer<QLabel> ImLabel;

	QPointer<QDockWidget> consoleDock;

	QPointer<Editor> console;

	QPointer<OmniThread> thread;
	
};
#endif