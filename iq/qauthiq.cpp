#include "qauthiq.h"

#include <QDebug>
#include <QDomDocument>

void QAuthIQ::parseElementFromChild(const QDomElement &element)
{
    QDomElement auth = element.firstChildElement("auth");
    m_app = auth.attribute("name");
    qDebug()<<"App Name:"<<m_app;
    m_from = element.attribute("from");
}

void QAuthIQ::toXmlElementFromChild(QXmlStreamWriter *writer) const
{
    writer->writeStartElement("auth");
    writer->writeAttribute("xmlns",NS_AUTH);
    writer->writeAttribute("name",m_app);
    writer->writeEndElement();
}

bool QAuthIQ::isAuthIQ(const QDomElement &elem)
{
    QDomElement el = elem.firstChildElement("auth");

    QString type = elem.attribute("type");
    QString tag = elem.tagName();

    if( tag.compare("iq") != 0 || type.compare("error")==0)
    {
        return false;
    }

    if ( el.isNull())
    {
        return false;
    }

    else
    {
        return true;
    }
}
void QAuthIQ::parse(const QDomElement &element)
{
    m_from = element.attribute("from");
    m_to = element.attribute("to");
    m_id = element.attribute("id");
    QDomElement el = element.firstChildElement("auth");
    m_app = el.attribute("name");
    qDebug()<<"From:"<<m_from;
}
