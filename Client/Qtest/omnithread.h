#pragma once
#ifndef OMNITHREAD_H
#define OMNITHREAD_H

#include "ImSender.h"
#include <QThread>
#include <iostream>
#include "Editor.h"
#include <QBuffer>

struct OmniThreadParams {
	OmniThreadParams& SetArgc(int argc) {
		this->_argc = argc;
		return *this;
	}

	OmniThreadParams& SetArgv(char** argv) {
		this->_argv = argv;
		return *this;
	}

	OmniThreadParams& SetEditor(Editor* editor) {
		this->_editor = editor;
		return *this;
	}
	OmniThreadParams& SetFilename(QString* filename) {
		this->_filename = filename;
		return *this;
	}
	OmniThreadParams& SetImageWidget(QLabel* image) {
		this->_image = image;
		return *this;
	}

	OmniThreadParams& SetStoreBuf(QByteArray* ba) {
		this->ba = ba;
		return *this;
	}
	OmniThreadParams& SetOrb(CORBA::ORB_var orb) {
		this->orb = orb;
		return *this;
	}
	OmniThreadParams& SetSender(ImageSender::Sender_var _manager) {
		this->manager = _manager;
		return *this;
	}

	int _argc;
	char** _argv;
	Editor* _editor;
	QString* _filename;
	QLabel* _image;
	QByteArray* ba;
	CORBA::ORB_var orb;
	ImageSender::Sender_var manager;
};
class OmniThread : public QThread {

	Q_OBJECT

public:
	OmniThread(const OmniThreadParams& params, QObject* parent);
	~OmniThread();
	

signals:
	void textChanged(const QString& str);
public slots:
	void ShutdownServer();
protected:
	void run();
	int _argc;
	char **_argv;
	Editor* _editor;
	QString* _filename;
	QLabel* _image;
	QByteArray* ba;
	CORBA::ORB_var orb;
	ImageSender::Sender_var manager;


private: 
	//OmniThread(int argc, char** argv, Editor* editor = NULL, QString* filename = NULL, QLabel* image = NULL, QObject* parent = NULL, QByteArray* ba = NULL);
	void InitConnect();
	void SendToServer(ImageSender::Sender_ptr e);	
};

#endif
