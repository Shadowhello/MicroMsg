#include "qxmpppacketconsle.h"
#include "session.h"
#include "CommandParse.hpp"
#include "qfiletrans.h"
#include "qlogindesktop.h"
#include "utils/defines.h"
#include "utils/qmessageproccesser.h"

#include "utils/qiqprocesser.h"

#include <QXmppUtils.h>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QVBoxLayout>


#ifndef LOCAL(X)
#define LOCAL(X) QString::fromLocal8Bit(X)
#endif


QXmppPacketConsle::QXmppPacketConsle(QWidget *parent) :
    QDialog(parent)//,
    //ui(new Ui::QXmppPacketConsle)
{
    //ui->setupUi(this);
    tip = new QTipDilog();
    initUI();
    resize(800,400);
    setWindowIcon(QIcon(":/UI/app.png"));
}

QXmppPacketConsle::~QXmppPacketConsle()
{
//    delete ui;
}
void QXmppPacketConsle::closeEvent(QCloseEvent *e)
{
    hide();
    saveHistory();
    e->ignore();
}

void QXmppPacketConsle::logMessage(QXmppLogger::MessageType type,QString msg)
{
    static int logcount = 0;
    int     ret = 0;

    ++logcount;
    if (logcount > MAX_MESSAGE_SHOW)
    {
        logcount = 0;
        saveHistory();
    }
    if ( type != QXmppLogger::ReceivedMessage && type != QXmppLogger::SentMessage)
        return;
    if (type == QXmppLogger::ReceivedMessage)
    {
        qDebug()<<"RECV:"<<msg;
        QRegExp reg("<message",Qt::CaseInsensitive);
        if ( msg.indexOf(reg) >= 0 )
        {
            //处理message报文
            TitleMsg tmsg;
            int ret = 0;
            QMessageProccesser proc;
            proc.GetTitleMsg(msg,tmsg,ret);
            if ( ret == Process_Fail )
            {
                //普通消息
                return;
            }
            emit SpecialMessage(tmsg.title,tmsg.from,tmsg.body);
            return;
        }else if ( msg.indexOf("iq",0,Qt::CaseInsensitive) >= 0 )
        {
            QDomDocument dom;

            if( dom.setContent(msg))
            {
                QDomElement root = dom.documentElement();
                QString to_usr = root.attribute("to","");
                to_usr = QXmppUtils::jidToUser(to_usr);
                QSettings set;
                set.setValue("login_usr",to_usr);
                return;
            }
        }
    }
    else if ( type == QXmppLogger::SentMessage)
    {
        msg = "Out:\n" + msg;
    }

}
void QXmppPacketConsle::returnPressed()
{

}

void QXmppPacketConsle::saveHistory()
{

}
void QXmppPacketConsle::iqReceived(const QXmppIq &iq)
{
    QString siq;
    QXmlStreamWriter *xmlwriter = new QXmlStreamWriter(&siq);
    iq.toXml(xmlwriter);
    qDebug()<<"\n======================IQ Received:========================\n"<<siq<<"\n\n";

}

void QXmppPacketConsle::initUI()
{
    QVBoxLayout *main = new QVBoxLayout(this);
    QWidget *center = new QWidget(this);
    QVBoxLayout *vlay = new QVBoxLayout(center);

    vlay->setMargin(0);
    m_web = new QHFWebView(center);

    vlay->addWidget(m_web);
    main->addWidget(center);
}
