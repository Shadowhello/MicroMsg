#ifndef QLOGINDESKTOP_H
#define QLOGINDESKTOP_H

#include "login/qfiletrans.h"
#include "utils/qhfwebview.h"
#include "login/qxmpppacketconsle.h"
#include "iq/qauthiqmanager.h"

#include <QXmppMessage.h>
#include <QWidget>
#include <QWebView>


class MainWidget;
class QLoginDesktop : public QWidget
{
    Q_OBJECT
public:
    explicit QLoginDesktop(QWidget *parent = 0);

    static QLoginDesktop *ref()
    {
        return m_login;
    }
    QFileTrans *getClient()
    {
        return m_client;
    }


    ~QLoginDesktop();
signals:

public slots:
    void    showMain();
    void    addObject();
    void    exitApp();
    void    msgBox(QString title,QString txt);
    void    caLogin(QString host,QString ip);
    void    upLogin(QString usr, QString pwd, QString host,QString ip);
    QStringList readConfig();
    void    setRoster();

    void    onSvrDownloadFinish(const char*, const char*);

    void    connected();
    void    disconnected();
    void    connectedError();
    void    csleep(int millisec);
    void    rosterReceive();

    void    show_tips(QString from,QString to,QString app,QString id);

protected:
    void    initUI();
    void    downloadSvrList();

    void     mousePressEvent(QMouseEvent*);
    void     mouseReleaseEvent(QMouseEvent*);
    void     mouseMoveEvent(QMouseEvent*);
private:

    static                      QLoginDesktop *m_login;
    QHFWebView                  *m_web;
    QFileTrans                  *m_client;
    MainWidget                  *m_mainwidget;
    QAuthIQManager              *m_authMana;

    QXmppPacketConsle           *m_consle;
    QStringList                 m_rosters;

    QPoint                      m_presssPoint;
    QPoint                      m_movePoint;
    bool                        m_pressed;
};

#endif // QLOGINDESKTOP_H
