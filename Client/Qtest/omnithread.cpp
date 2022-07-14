
#include "omnithread.h"
#include <QDebug>
#include <memory>

::ImageSender::Sender::image BuildImageSeq(const QByteArray& ba) {
	::ImageSender::Sender::image outseq = ::ImageSender::Sender::image();
	outseq.length(ba.size());
	for (int i = 0; i < ba.size(); ++i) {
		outseq[i] = ba[i];
	}
	return outseq;
}

void OmniThread::InitConnect() {
	orb = CORBA::ORB_init(_argc, _argv);
	CORBA::Object_var obj = orb->string_to_object(_argv[1]);
	CORBA::String_var sior(orb->object_to_string(obj));
	qDebug() << (char*)sior << "\n";
	manager = ImageSender::Sender::_narrow(obj);

	if (CORBA::is_nil(manager)) {
		emit textChanged("error: Can't narrow reference to type Echo (or it was nil).\n");
		exit(1);
	}		
}

OmniThread::OmniThread(const OmniThreadParams& params, QObject* parent) : QThread(parent)
{
	_argc = params._argc;
	_argv = params._argv;
	_editor = params._editor;
	_filename = params._filename;
	_image = params._image;
	ba = params.ba;
	orb = params.orb;
	manager = params.manager;
}


OmniThread::~OmniThread() {
	qDebug() << "OmniThread is over\n";
	orb->destroy();

}
void OmniThread::ShutdownServer() {
	if (orb == CORBA::ORB_var() ||CORBA::is_nil(orb)) {
		emit textChanged("warning: nothing to disconnect!\n");
		return;
	}
	try {
		manager->shutdown();
	}
	catch (CORBA::TRANSIENT&) {
		QString str = QString("warning: nothing to disconnect!\n");
		emit textChanged(str);
	}
	qDebug()<<"server is shutdown!\n";
}
void OmniThread::SendToServer(ImageSender::Sender_ptr e) {
	if (_filename->isEmpty()) {
		emit textChanged("error: nothing to send\n");
		return;
	}
	else if (CORBA::is_nil(e)) {
		QString str = QString("error: The object reference is nil!\n");
		emit textChanged(str);
		return;
	}
	ba->clear();
	QBuffer buff(ba);
	buff.open(QIODevice::WriteOnly);
	if (_image->pixmap()->save(&buff, "PNG")) {
		::ImageSender::Sender::image  outseq = std::move(BuildImageSeq(*ba));
		if (e->Send(_filename->toLocal8Bit().data(), _filename->size(), outseq)) {
			emit textChanged("OK: successfully sent image to the server " + QString(*_filename) + "");
		}
	}
	else {
		emit textChanged("error: can't send file " + QString(*_filename) + "");
		return;
	}
}

void OmniThread::run() {
	qDebug() << "Running  run client "<< QThread::currentThread()<<"\n";

	try {
		if (CORBA::is_nil(orb) || CORBA::is_nil(manager)) {
			InitConnect();
		}
		emit textChanged("Try to send...");
		OmniThread::SendToServer(manager);
	}
	catch (CORBA::TRANSIENT&) {
		QString str = QString("error: Caught system exception TRANSIENT -- unable to contact the server\n");
		emit textChanged(str);
	}
	catch (CORBA::SystemException& ex) {

		QString str = QString("error: Caught a CORBA::") + QString(ex._name()) + QString("\n");
		emit textChanged(str);
	}
	catch (CORBA::Exception& ex) {
		QString str = QString("error: Caught a CORBA::") + QString(ex._name()) + QString("\n");
		emit textChanged(str);
	}
	catch (omniORB::fatalException& fe) {
		QString str = QString("error: Caught omniORB::fatalException:\n") +
			QString("  file: ") + QString(fe.file()) + QString("\n") +
			QString("  line: ") + QString(fe.line()) + QString("\n") +
			QString("  mesg: ") + QString(fe.errmsg()) + QString("\n");
		emit textChanged(str);
	}
}