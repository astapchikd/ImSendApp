#include "MyWindow.h"

MyWindow::MyWindow(int argc, char** argv, QWidget* parent) : QMainWindow(parent), _argc(argc), _argv(argv) {

	init();

	resize(400, 400);
	setWindowTitle("Image Sender Server GUI");

}

void MyWindow::init() {
	initActions();
	initMainMenu();
	initToolBars();
	initStatusBar();
	initCentralWidget();
	initConsoleDock();
	initThread();
	
}

void MyWindow::initActions() {
	aSave = new QAction(QPixmap("Resources/Save.png"), "Save", this);
	aSaveAs = new QAction(QPixmap("Resources/SaveAs.png"), "SaveAs", this);
	aClear = new QAction(QPixmap("Resources/Clear.png"), "Clear", this);
	aRun = new QAction(QPixmap("Resources/Run.png"), "Run", this);
	aAbout = new QAction(QPixmap("Resources/Font.png"), "About", this);

	connect(aSaveAs, SIGNAL(triggered()), SLOT(slotSaveAs()));
	connect(aSave, SIGNAL(triggered()), SLOT(slotSave()));
	connect(aClear, SIGNAL(triggered()), SLOT(slotClear()));
	connect(aAbout, SIGNAL(triggered()), SLOT(slotAbout()));
	connect(aRun, SIGNAL(triggered()), SLOT(slotRun()));
	

}

void MyWindow::initMainMenu() {
	mFile = new QMenu("File", this);
	mSend = new QMenu("Send",this);
	mHelp = new QMenu("Help", this);
	mFile->addAction(aSave);
	mFile->addAction(aSaveAs);
	mFile->addAction(aClear);
	mSend->addAction(aRun);
	mHelp->addAction(aAbout);
	menuBar()->addMenu(mFile);
	menuBar()->addMenu(mSend);
	menuBar()->addMenu(mHelp);
}

void MyWindow::initToolBars() {
	toolbar = new QToolBar(this);
	toolbar->addSeparator();
	toolbar->addAction(aSave);
	toolbar->addAction(aSaveAs);
	toolbar->addAction(aClear);
	toolbar->addAction(aRun);
	toolbar->addAction(aExit);
	toolbar->addAction(aAbout);

	addToolBar(Qt::TopToolBarArea, toolbar);
}

void MyWindow::initStatusBar() {
	QStatusBar* bar = new QStatusBar(this);
	if (filename.isEmpty()) {
		bar->showMessage("Ready to work!");
	}
	else {
		bar->showMessage(filename);
	}
	setStatusBar(bar);
}

void MyWindow::initCentralWidget() {
	ImLabel = new QLabel();
	ImLabel->setAlignment(Qt::AlignCenter);
	ImLabel->setPixmap(QPixmap(filename));
	ImLabel->show();
	setCentralWidget(ImLabel);
}

void MyWindow::initConsoleDock() {
	consoleDock = new QDockWidget("Console", this);
	consoleDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
	consoleDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	addDockWidget(Qt::LeftDockWidgetArea, consoleDock);
	console = new Editor(1, consoleDock);
	consoleDock->setWidget(console);
	

}

void MyWindow::initThread() {
	thread = new OmniThread(_argc, _argv, console, &filename, ImLabel,this);
	connect(thread,SIGNAL(textChanged(const QString&)),this,SLOT(textChanged(const QString&)));
	connect(thread, SIGNAL(finished()),thread, SLOT(deleteLater()));
}

void MyWindow::slotSaveAs() {
	QString filename;
	filename = QFileDialog::getSaveFileName(
		this,
		"Select",
		"",
		"All (*);; PNG (*.png)"
	);
	if (filename.isEmpty() || filename.isNull()) return;
	if (ImLabel->pixmap()->save(filename)) {
		emit textChanged("OK: file " + filename + "succsesfully saved");
		QStatusBar* bar = new QStatusBar(this);
		bar->showMessage(filename);
		setStatusBar(bar);
	}
}

void MyWindow::slotSave() {
	if (filename.isEmpty() || filename.isNull()) return;
	QString filepath = QString("ImageStore/") + filename;
	if (ImLabel->pixmap()->save(filepath)) {
		emit textChanged("OK: file " + filename + "succsesfully saved");
		QStatusBar* bar = new QStatusBar(this);
		bar->showMessage(filepath);
		setStatusBar(bar);
	}
}

void MyWindow::slotRun() {
	qDebug() << "running start Server " << QThread::currentThread() << "\n";
	thread->start();
}

void MyWindow::slotClear() {
	filename.clear();
	ImLabel->clear();
	ImLabel->show();
	QStatusBar* bar = new QStatusBar(this);
	bar->showMessage(filename);
	setStatusBar(bar);
}

void MyWindow::slotAbout() {
	QMessageBox msgBox;
	msgBox.setText("This programm using for send Image to Server");
	msgBox.setInformativeText("developed by Astapchik D.");
	msgBox.setIconPixmap(QPixmap("Resources/Russian.png"));
	msgBox.setDefaultButton(QMessageBox::Ok);
	int res = msgBox.exec();
	if (res == QMessageBox::Ok)
		msgBox.close();
}

void MyWindow::textChanged(const QString& str) {
	console->appendPlainText(str);
}

