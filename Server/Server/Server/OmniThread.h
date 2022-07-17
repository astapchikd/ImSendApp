#ifndef OMNIORBTHREAD_H
#define OMNIORBTHREAD_H
#include "ImSender.h"
#include <QThread>
#include <iostream>
#include "Editor.h"
#include <string>

class ImageSenderImpl : virtual public POA_ImageSender::Sender, virtual public PortableServer::RefCountServantBase {

public:
	ImageSenderImpl(Editor* editor = nullptr, QString* filename = nullptr, QLabel* image = nullptr, CORBA::ORB_var* orb = nullptr);
	virtual ~ImageSenderImpl();
	virtual ::CORBA::Boolean Send(const char* filename, ::CORBA::Long sizefname, const ::ImageSender::Sender::image& im);
	virtual ::CORBA::Boolean shutdown();
private:
	Editor* _editor;
	QString* _filename;
	QLabel* _image;
	CORBA::ORB_var* _orb;
};


class OmniThread : public QThread {

	Q_OBJECT
public:
	explicit OmniThread(int argc, char** argv, Editor* editor = nullptr, QString* filename = nullptr, QLabel* image = nullptr,QObject* parent = nullptr);
	~OmniThread();
signals:
	void textChanged(const QString& str);
protected:
	void run();
	int _argc;
	char** _argv;
	CORBA::ORB_var orb;
	Editor* _editor;
	QString* _filename;
	QLabel* _image;
};

#endif
