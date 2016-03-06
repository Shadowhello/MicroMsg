#include "qauthiqmanager.h"

#include "iq/qauthiq.h"
#include "utils/qiqprocesser.h"
#include "login/qlogindesktop.h"

#include <QDebug>

QAuthIQManager::QAuthIQManager():QXmppClientExtension(),tip( new QTipDilog())
{
    connect(this,SIGNAL(show_tips_sig(QString,QString,QString,QString)),
            this,SLOT(show_tips(QString,QString,QString,QString)));
}
QAuthIQManager::~QAuthIQManager()
{
    delete tip;
}

bool QAuthIQManager::handleStanza(const QDomElement &stanza)
{
    if ( !QAuthIQ::isAuthIQ(stanza) )
    {
        return false;
    }
    QAuthIQ auth;
    auth.parse(stanza);
    emit show_tips_sig(auth.getFrom(),auth.getTo(),auth.getAppName(),auth.getid());
    return true;
}
void QAuthIQManager::show_tips(QString from,QString to,QString app,QString id)
{
    QTipDilog *tipDlg = tip;
    QIQProcesser proc;
    proc.setAppName(app);
    proc.setFrom(from);
    proc.setTo(to);
    proc.setid(id);
    qDebug()<<"App Name:"<<app;
    tipDlg->setIQProc(&proc);
    tipDlg->setClient(QLoginDesktop::ref()->getClient());
    tipDlg->exec();
}
