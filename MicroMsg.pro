#-------------------------------------------------
#
# Project created by QtCreator 2015-12-16T09:28:08
#
#-------------------------------------------------

QT       += core gui webkit network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MicroMsg
TEMPLATE = app


SOURCES += main.cpp\
    utils/qapputils.cpp \
    utils/qhfwebview.cpp \
    jsCore/qjscore.cpp \
    login/caoper.cpp \
    login/qfiletrans.cpp \
    login/qlogindesktop.cpp \
    login/qutil.cpp \
    login/qxmpppacketconsle.cpp \
    login/session.cpp \
    utils/qmessageproccesser.cpp \
    utils/qiqprocesser.cpp \
    uiframe/qtipdilog.cpp \
    iq/qauthiq.cpp \
    iq/qauthiqmanager.cpp \
    ipc/cnamedpiple.cpp \
    ipc/pipes.cpp \
    mainwidget.cpp \
    md5/md5.cpp \
    softCenter/qsoftcenter.cpp \
    http/qhttpdownload.cpp

HEADERS  += mainwidget.h \
    utils/defines.h \
    utils/qapputils.h \
    utils/qhfwebview.h \
    jsCore/qjscore.h \
    login/caoper.h \
    login/CommandParse.hpp \
    login/datatypes.h \
    login/qfiletrans.h \
    login/qlogindesktop.h \
    login/qutil.h \
    login/qxmpppacketconsle.h \
    login/session.h \
    utils/qmessageproccesser.h \
    utils/qiqprocesser.h \
    qtipdilog.h \
    uiframe/qtipdilog.h \
    iq/qauthiq.h \
    iq/qauthiqmanager.h \
    ipc/cnamedpiple.h \
    ipc/pipes.h \
    md5/md5.h \
    softCenter/qsoftcenter.h \
    http/qhttpdownload.h

FORMS    += mainwidget.ui

DEFINES += _UNICODE

LIBS += user32.lib shell32.lib ole32.lib


INCLUDEPATH += "F:\C-C++\HF-Soft\qxmpp\qxmpp-master\src\client"
INCLUDEPATH += "F:\C-C++\HF-Soft\qxmpp\qxmpp-master\src\base"
INCLUDEPATH += "F:\C-C++\libpool\include"

LIBS+="F:\C-C++\libpool\lib\Pool.lib"
LIBS += "F:\C-C++\HF-Soft\qxmpp\build-qxmpp-unknown-Debug\src\qxmpp_d0.lib"
