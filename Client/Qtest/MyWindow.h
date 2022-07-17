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
#include <memory>

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
signals:
	void ShutdownServer();
	//�����
public slots:
	void slotOpen();				//���� �������� �����
	void slotSaveAs();
	void slotClear();
	void slotRun();
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
	QPointer<QAction> aOpen;			
	QPointer<QAction> aSaveAs;
	QPointer<QAction> aExit;			
	QPointer<QAction> aClear;
	QPointer<QAction> aRun;

	QPointer<QToolBar> toolbar;

	QString filename;
	QString filepath;

	QPointer<QLabel> ImLabel;

	QPointer<QDockWidget> consoleDock;

	QPointer<Editor> console;

	std::unique_ptr<QByteArray> ba;

	QPointer <OmniThread> thread;
	
};
#endif