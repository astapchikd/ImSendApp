set MOC=B:/dev/Qt5.12/5.12.12/msvc2017/bin/moc.exe
%MOC% -o moc_CodeEditor.cpp CodeEditor.h
%MOC% -o moc_Editor.cpp Editor.h
%MOC% -o moc_ImSender.cpp ImSender.h
%MOC% -o moc_omnithread.cpp omnithread.h
%MOC% -o moc_MyWindow.cpp MyWindow.h
exit