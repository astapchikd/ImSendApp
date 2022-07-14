#include "OmniThread.h"


::CORBA::Boolean ImageSenderImpl::Send(const char* filename, ::CORBA::Long sizefname, const ::ImageSender::Sender::image& im) throw(::CORBA::SystemException) {
	qDebug() << "running in Send Server " << QThread::currentThread() << "\n";
	*_filename = QString(QByteArray(filename, sizefname));
	QByteArray ba = QByteArray((const char*)im.get_buffer(),im.length());
	QPixmap pp;
	if (pp.loadFromData(ba, "PNG")) {
		_image->clear();
		_image->setPixmap(pp);
		qDebug() << QString("OK: recieved file " + *_filename + " size of " + im.length()) << "\n";
		return true;
	}
	qDebug() << QString("error: cant'load file " + *_filename + " size of " + im.length() + "\n");
	return false;
}

::CORBA::Boolean ImageSenderImpl::shutdown() throw(::CORBA::SystemException) {
	(*_orb)->shutdown(false);
	return true;
}

ImageSenderImpl::ImageSenderImpl(Editor* editor , QString* filename, QLabel* image , CORBA::ORB_var* orb) : _editor(editor), _filename(filename), _image(image), _orb(orb)
{}

ImageSenderImpl::~ImageSenderImpl() 
{
	qDebug() << "SenderDestroyed\n";
}

OmniThread::OmniThread(int argc, char** argv, Editor* editor , QString* filename , QLabel* image, QObject* parent) : QThread(parent), _argc(argc), _argv(argv), _editor(editor), _filename(filename), _image(image)
{

}

OmniThread::~OmniThread() {
	qDebug() << "OmniThread is over\n";
}

void OmniThread::run() {
	qDebug() << "running run Server " << currentThread() << "\n";
	ImageSenderImpl* ImSeI = nullptr;
	CORBA::ORB_var orb;
	try {
		CORBA::ORB_var orb = CORBA::ORB_init(_argc, _argv);
		CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
		PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
		ImSeI = new ImageSenderImpl(_editor, _filename, _image, &orb);
		poa->activate_object(ImSeI);
		obj = ImSeI->_this();
		CORBA::String_var sior(orb->object_to_string(obj));
		qDebug() << (char*)sior << "\n";

		ImSeI->_remove_ref();

		PortableServer::POAManager_var pman = poa->the_POAManager();
		pman->activate();
		orb->run();	
	}
	catch (const CORBA::Exception& e) {
		QString str = QString("error: ") + QString(e._name()) + QString('\n');
		emit textChanged(str);
	}

	if (!CORBA::is_nil(orb)) {
		try {
			orb->destroy();
			QString str = QString("Ending CORBA...\n");
			emit textChanged(str);
		}
		catch (const CORBA::Exception& e)
		{
			QString str = QString("error: orb->destroy() failed:") + QString(e._name()) + QString('\n');
			emit textChanged(str);
		}
	}
}