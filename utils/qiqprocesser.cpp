#include "qiqprocesser.h"

#include <QDomDocument>

QIQProcesser::QIQProcesser(QObject *parent) :
    QObject(parent)
{

}


QIQProcesser* QIQProcesser::parseXml(const QString &msg)
{
    static QIQProcesser iqproc;

    QDomDocument    doc;
    if ( !doc.setContent(msg))
    {
        return NULL;
    }
    QDomElement     root = doc.documentElement();
    QDomElement     elem = root.firstChildElement("auth");

    m_to = root.attribute("to","");
    m_from = root.attribute("from","");
    QString type = root.attribute("type");
    qDebug()<<"Type:"<<type;

    if ( root.attribute("type").compare("error") == 0 )
    {
        return NULL;
    }
    if ( elem.isNull() )
    {
        return NULL;
    }

    QString app = elem.attribute("name","");
    iqproc.setAppName(app);
    iqproc.setFrom(m_from);

    return &iqproc;
}

void QIQProcesser::sendYes(QXmppClient *client)
{
    QString res;
    res.append("<iq to=\"").append(getFrom()).append("\" type=\"result\" from=\"").append(getTo()).append("\" ");
    res.append("id=\"").append(getId()).append("\">");
    res.append("<auth xmlns=\"hf.safe.auth\" name=\"").append(getAppName()).append("\" result=\"Yes\"></auth></iq>");
    qDebug()<<"Send To:"<<res;
    client->sendData(res);
}
void QIQProcesser::sendNo(QXmppClient *client)
{
    QString res;
    res.append("<iq to=\"").append(getFrom()).append("\" type=\"result\" from=\"").append(getTo()).append("\">");
    res.append("<auth xmlns=\"hf.safe.auth\" name=\"").append(getAppName()).append("\" result=\"No\"></auth></iq>");
    qDebug()<<"Send To:"<<res;
    client->sendData(res);
}
