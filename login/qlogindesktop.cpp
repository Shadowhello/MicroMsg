#include "qlogindesktop.h"
#include "caoper.h"
#include "utils/defines.h"
#include "jsCore/qjscore.h"



#include "mainwidget.h"



#include <QHBoxLayout>
#include <QWebSettings>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>
#include <QNetworkCookieJar>
#include <QWebFrame>

#include <QXmppRosterManager.h>

QLoginDesktop* QLoginDesktop::m_login = NULL;

QLoginDesktop::QLoginDesktop(QWidget *parent) : QWidget(parent),m_mainwidget(NULL)
{
    initUI();
    resize(400,660);

    m_client = new QFileTrans(this);
    m_login = this;
    m_consle = new QXmppPacketConsle(this);
    m_authMana = new QAuthIQManager();




    qRegisterMetaType<QStringList>("QStringList");
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->showFullScreen();

    m_client->addExtension(m_authMana);

    connect(&m_client->rosterManager(),SIGNAL(rosterReceived()),this,SLOT(rosterReceive()));
    connect(m_client,SIGNAL(connected()),this,SLOT(connected()));
    connect(m_client,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(m_client,SIGNAL(iqReceived(QXmppIq)),m_consle,SLOT(iqReceived(QXmppIq)));
    connect(m_client,SIGNAL(logMessage(QXmppLogger::MessageType,QString)),m_consle,SLOT(logMessage(QXmppLogger::MessageType,QString)));
}
QLoginDesktop::~QLoginDesktop()
{
    qDebug()<<"QLoginDesktop destroy";
    if( NULL != m_mainwidget)
        delete m_mainwidget;
}

void QLoginDesktop::initUI()
{
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setContentsMargins(0,0,0,0);
    m_web = new QHFWebView(this);
    m_web->load(QUrl("html/login.html"));
    m_web->setTransparent(true);
    m_web->page()->networkAccessManager()->setCookieJar(new QNetworkCookieJar(this));
    QWebSettings    *webSetting = m_web->page()->settings();
    webSetting->setAttribute(QWebSettings::JavascriptEnabled,true);
    connect(m_web->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addObject()));
    lay->addWidget(m_web);

}

void QLoginDesktop::addObject()
{
    m_web->page()->mainFrame()->addToJavaScriptWindowObject("Login",this);
}

void QLoginDesktop::showMain()
{
    qDebug()<<"Show Main";
    m_mainwidget = new MainWidget(0);
//    m_mainwidget->show();
    m_mainwidget->toTray();

    connect(m_consle,SIGNAL(SpecialMessage(QString,QString,QString)),m_mainwidget,SLOT(SpecialMessage(QString,QString,QString)));
    this->hide();
}
void QLoginDesktop::exitApp()
{
    qApp->exit(0);
}
void QLoginDesktop::msgBox(QString title, QString txt)
{
    QMessageBox::information(this,title,txt,0);
}
void QLoginDesktop::caLogin(QString host,QString ip)
{
    QString         qorigin = CAOper::getOrigin();
    QString         usr;
    CAOper          oper;
    QString         sign = oper.buildAuthRequest(tr(""),qorigin);
    QSettings       set;
    qDebug()<<"CALogin Host:"<<host<<" Ip:"<<ip;
    qDebug() <<"Sign:"<<sign;
    usr = qorigin;
    qDebug()<<"Usr:"<<usr;
    m_client->login(usr,sign,host,ip,QFileTrans::CA);
}
void QLoginDesktop::upLogin(QString usr, QString pwd, QString host, QString ip)
{
    qDebug()<<"Login.........";
    m_client->login(usr,pwd,host,ip);
}

QStringList  QLoginDesktop::readConfig()
{
    QSettings   set;
    downloadSvrList();
    QString usr = set.value("usr","").toString();
    QString svr = set.value("svr","").toString();
    QString ip  = set.value("ip","127.0.0.1").toString();
    QString pwd = set.value("pwd","").toString();
    if (ip.isEmpty())
    {
        ip = "127.0.0.1";
        set.setValue("ip",ip);
    }
    return QStringList()<<usr<<pwd<<svr<<ip;
}

void QLoginDesktop::connected()
{
    showMain();
}
void QLoginDesktop::disconnected()
{
    QSettings set;
    set.setValue("login_usr","");
}

void QLoginDesktop::connectedError()
{
    msgBox(LOCAL("错误"),LOCAL("未登陆"));
}

void QLoginDesktop::csleep(int millisec)
{
    Sleep(millisec);
}

void QLoginDesktop::downloadSvrList()
{

}
void QLoginDesktop::onSvrDownloadFinish(const char *, const char *)
{

}
void QLoginDesktop::rosterReceive()
{
    m_rosters = m_client->rosterManager().getRosterBareJids();
}
void QLoginDesktop::show_tips(QString from, QString to, QString app, QString id)
{

}

void QLoginDesktop::setRoster()
{
    if ( m_rosters.size() <= 0 )
    {
        return;
    }
    qDebug()<<"Set Rosters:"<<m_rosters.at(0);
    m_mainwidget->getWebView()->page()->mainFrame()->evaluateJavaScript("$(this).clearRoster()");
    foreach (const QString roster, m_rosters) {
        QString js = "$(this).addRoster('"+roster + "')";
        qDebug()<<js;
        m_mainwidget->getWebView() ->page()->mainFrame()->evaluateJavaScript(js);
    }
}

void QLoginDesktop::mousePressEvent(QMouseEvent *evt)
{
    if(evt->button() != Qt::LeftButton)
    {
        m_pressed = false;
    }
    else
    {
        m_pressed = true;
        m_movePoint = evt->globalPos()-pos();
    }
}
void QLoginDesktop::mouseReleaseEvent(QMouseEvent *)
{
    m_pressed = false;
    update();
}
void QLoginDesktop::mouseMoveEvent(QMouseEvent *evt)
{
    if ( m_pressed)
    {
        move(evt->globalPos() - m_movePoint);
    }
    update();
}



