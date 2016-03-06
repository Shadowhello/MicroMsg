#include "mainwidget.h"
#include "login/qlogindesktop.h"
#include "uiframe/qtipdilog.h"

#include <QTextCodec>
#include <QApplication>

int main(int argc, char *argv[])
{

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    QApplication a(argc, argv);
//    MainWidget w;
//    w.show();

    QCoreApplication::setOrganizationName("HF-Soft");
    QCoreApplication::setOrganizationDomain("hf.com");
    QCoreApplication::setApplicationName("desk");

    QLoginDesktop login;
    login.show();
    return a.exec();
}
