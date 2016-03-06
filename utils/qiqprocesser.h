#ifndef QIQPROCESSER_H
#define QIQPROCESSER_H

#include <QObject>
#include <QXmppClient.h>

class QIQProcesser : public QObject
{
    Q_OBJECT
public:
    explicit QIQProcesser(QObject *parent = 0);

    ~QIQProcesser(){}

    QIQProcesser* parseXml(const QString &msg);

    void         setAppName( const QString &s)
    {
        m_appname = s;
    }
    QString getAppName()
    {
        return m_appname;
    }

    void        sendYes(QXmppClient *client);
    void        sendNo(QXmppClient *client);

    void        setTo(const QString to){ m_to = to;}
    QString     getTo() const    { return m_to;}

    void        setid(const QString id) { m_id = id;}
    QString     getId() const { return m_id;}
    void        setFrom(const QString frm) { m_from = frm;}
    QString     getFrom() { return m_from; }

signals:

public slots:

private:
    QString             m_appname;
    QString             m_from;
    QString             m_to;
    QString             m_id;
};

#endif // QIQPROCESSER_H
