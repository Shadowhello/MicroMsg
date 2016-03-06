#include "qjscore.h"
#include "utils/defines.h"
#include "login/qutil.h"
#include "login/session.h"
#include "login/qlogindesktop.h"

#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
#include <string>
#include <QApplication>
#include <QTextCodec>
#include <Windows.h>
#include <ShellAPI.h>
#include <QTextCodec>
#include <QTextStream>
#include <QSettings>
#include <QClipboard>

using namespace std;


QJSCore::QJSCore(QObject *parent) : QObject(parent)
{
    //m_acct = new QAccountMgr( & MainDialog::ref());
}
QJSCore::~QJSCore()
{

}
void QJSCore::saveData(const QString &fn, const QString &data)
{
    QFile file(fn);
    if ( ! file.open( QIODevice::WriteOnly ))
    {
        return;
    }
    QTextStream output( &file );
    output.setCodec("utf-8");
    output<<data;
    file.close();
}

QString QJSCore::readFromFile(const QString &fn)
{
    QString result;
    QFile file(fn);
    qDebug()<<fn;
    if ( !file.exists() )
    {
        qDebug()<<"No This File";
        return result;
    }
    file.open(QIODevice::ReadOnly);
    result = QString::fromUtf8(file.readAll());
    qDebug()<<result;
    file.close();
    return result;
}

void QJSCore::msgBox(const QString &title,const QString &txt)
{
    qDebug()<<"MsgBox";
    QMessageBox::information(NULL,title,txt,0);
}
void QJSCore::close()
{
    qApp->exit(0);
}
void QJSCore::exec(const QString &path)
{
    QFile file(path);
    ShellExecuteA(0,"open",path.toLocal8Bit().data(),NULL,NULL,SW_SHOW);
}
void QJSCore::open(const QString &path)
{

    QFile file(path);
    if( file.exists())
    {
        qDebug()<<"Open:"<<path;
        QProcess *proc = new QProcess(this);
        proc->start(path);
        proc->waitForStarted(5000);
    }else
    {
        qDebug()<<"No File:"<<path;
    }
}
void QJSCore::open(const QString &path, const QStringList &arglist)
{
    QFile file(path);
    for ( int i = 0 ; i < arglist.count(); ++i)
    {
        qDebug()<<arglist.at(i);
    }

    if( file.exists())
    {
        qDebug()<<"Open:"<<path;
        QProcess *proc = new QProcess(this);
        proc->start(path,arglist);
        proc->waitForStarted(5000);

    }else
    {
        qDebug()<<"No File:"<<path;
    }
}


QString QJSCore::nameFromURL(QString url)
{
    QFileInfo info(url);
    return info.fileName();
}


void QJSCore::saveValue(QString key, QString value)
{
    QSettings   set;
    qDebug()<<"set key:"<<key<<" value:"<<value;
    set.setValue(key,value);
}
QString QJSCore::readValue(QString key)
{
    QSettings set;
    return set.value(key).toString();
}

QString QJSCore::getDCode()
{
    QString code = QUtil::Instance()->createDCode();
    qDebug()<<"Dynamic Code is:"<<code;

    return code;
}

void QJSCore::sendData(QString title, QString to, QString body)
{


}
void QJSCore::setRoster()
{
    QLoginDesktop::ref()->setRoster();
}

void QJSCore::sendData(QString msg)
{
    qDebug()<<"Origin:"<<msg;
    QString str = QString::fromLocal8Bit(msg.toLocal8Bit().data());
    qDebug()<<"Change:"<<str;
    QLoginDesktop::ref()->getClient()->sendData(str.toUtf8());
}

