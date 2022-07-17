#include "MyWindow.h"

MyWindow::MyWindow(int argc, char** argv, QWidget* parent) : QMainWindow(parent), _argc(argc), _argv(argv) {

	init();

	resize(400, 400);
	setWindowTitle("Image Sender Client");

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
	aExit = new QAction(QPixmap("Resources/Exit.png"), "Exit", this);
	aOpen = new QAction(QPixmap("Resources/Open.png"), "Open", this);
	aSaveAs = new QAction(QPixmap("Resources/SaveAs.png"), "SaveAs", this);
	aClear = new QAction(QPixmap("Resources/Clear.png"), "Clear", this);
	aRun = new QAction(QPixmap("Resources/Run.png"), "Run", this);
	aAbout = new QAction(QPixmap("Resources/Font.png"), "About", this);

	//connect(aExit, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect(aOpen, SIGNAL(triggered()), SLOT(slotOpen()));
	connect(aSaveAs, SIGNAL(triggered()), SLOT(slotSaveAs()));
	connect(aClear, SIGNAL(triggered()), SLOT(slotClear()));
	connect(aAbout, SIGNAL(triggered()), SLOT(slotAbout()));
	connect(aRun, SIGNAL(triggered()), SLOT(slotRun()));
	

}

void MyWindow::initMainMenu() {
	mFile = new QMenu("File", this);
	mSend = new QMenu("Send",this);
	mHelp = new QMenu("Help", this);
	mFile->addAction(aOpen);
	mFile->addAction(aSaveAs);
	mFile->addAction(aClear);
	mFile->addAction(aExit);
	mSend->addAction(aRun);
	mHelp->addAction(aAbout);
	menuBar()->addMenu(mFile);
	menuBar()->addMenu(mSend);
	menuBar()->addMenu(mHelp);
}

void MyWindow::initToolBars() {
	toolbar = new QToolBar(this);
	toolbar->addAction(aOpen);
	toolbar->addSeparator();
	toolbar->addAction(aSaveAs);
	toolbar->addAction(aClear);
	toolbar->addAction(aRun);
	toolbar->addAction(aExit);
	toolbar->addAction(aAbout);

	addToolBar(Qt::TopToolBarArea, toolbar);
}

void MyWindow::initStatusBar() {
	QStatusBar* bar = new QStatusBar(this);
	if (filepath.isEmpty()) {
		bar->showMessage("Ready to work!");
	}
	else {
		bar->showMessage(filepath);
	}
	setStatusBar(bar);
}

void MyWindow::initCentralWidget() {
	ImLabel = new QLabel();
	ImLabel->setAlignment(Qt::AlignCenter);
	ImLabel->setPixmap(QPixmap(filepath));
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
	ba = std::make_unique<QByteArray>();
	thread = new OmniThread(
		OmniThreadParams().SetArgc(_argc).SetArgv(_argv).SetEditor(console)
		.SetFilename(&filename).SetImageWidget(ImLabel)
		.SetOrb(CORBA::ORB_var()).SetStoreBuf(ba.get())
		.SetSender(ImageSender::Sender_var()),this);
	connect(thread, SIGNAL(textChanged(const QString&)), this, SLOT(textChanged(const QString&)));
	connect(aExit, SIGNAL(triggered()), thread, SLOT(ShutdownServer()));
	//connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
}

void MyWindow::slotOpen() {
	QString filepathtmp = QFileDialog::getOpenFileName(
		this,
		"Select",
		"",
		"All (*);; PNG (*.png)"
	);
	if (filepathtmp.isEmpty()) {
		return;
	}
	filepath = std::move(filepathtmp);
	filename = filepath.split('/').back();
	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	ImLabel->setPixmap(QPixmap(filepath));
	ImLabel->show();
	file.close();
	QStatusBar* bar = new QStatusBar(this);
	bar->showMessage(filepath);
	setStatusBar(bar);
}

void MyWindow::slotSaveAs() {
	QString filename;
	filename = QFileDialog::getSaveFileName();
	if (filename.isEmpty() || filename.isNull()) return;
	ImLabel->pixmap()->save(filename);
}

void MyWindow::slotRun() {
	qDebug() << "Running client thread" << QThread::currentThread() << "\n";
	thread->start();
}

void MyWindow::slotClear() {
	filepath.clear();
	filename.clear();
	ImLabel->clear();
	ImLabel->show();
	QStatusBar* bar = new QStatusBar(this);
	bar->showMessage(filepath);
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
