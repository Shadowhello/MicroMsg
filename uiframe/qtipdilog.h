#ifndef QTIPDILOG_H
#define QTIPDILOG_H

#include "utils/qhfwebview.h"
#include "utils/qiqprocesser.h"

#include <QXmppClient.h>
#include <QDialog>

#include<QHash>
#include <QDateTime>

#define         VALID_TIME  10800

class QTipDilog : public QDialog
{
    Q_OBJECT
public:
    explicit QTipDilog(QWidget *parent = 0);
    ~QTipDilog(){}

    void            setClient(QXmppClient *c) { m_client = c;}
    void            setIQProc(QIQProcesser *iq);

    void            exec();
protected:
    void            initUI();
signals:

public slots:
    void            setYes(QString to);
    void            setNo(QString to);

    void            regObject();
private:

    QHFWebView      *m_web;
    QXmppClient     *m_client;
    QIQProcesser    *m_iqproc;
};

#endif // QTIPDILOG_H
