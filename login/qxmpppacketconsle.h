#ifndef QXMPPPACKETCONSLE_H
#define QXMPPPACKETCONSLE_H

#include "QXmppLogger.h"
#include "utils/qhfwebview.h"

#include "uiframe/qtipdilog.h"

#include <QXmppIq.h>
#include <QDialog>
#include <QCloseEvent>

#define     MAX_MESSAGE_SHOW    10240

namespace Ui {
class QXmppPacketConsle;
}

class QXmppPacketConsle : public QDialog
{
    Q_OBJECT

public:
    explicit QXmppPacketConsle(QWidget *parent = 0);

    ~QXmppPacketConsle();
    void closeEvent(QCloseEvent*);
    void returnPressed();

protected:
    void    initUI();
public slots:
    void    logMessage(QXmppLogger::MessageType,QString);
    void    iqReceived(const QXmppIq &iq);

protected:
    void    saveHistory();
signals:
    void    SpecialMessage(QString title,QString from,QString body);
private:
    Ui::QXmppPacketConsle *ui;

    QHFWebView  *m_web;
    QTipDilog   *tip;

};

#endif // QXMPPPACKETCONSLE_H
