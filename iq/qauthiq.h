#ifndef QAUTHIQ_H
#define QAUTHIQ_H

#include "utils/defines.h"

#include <QXmppIq.h>
#include <QObject>


class QAuthIQ : public QXmppIq
{
public:

    static bool isAuthIQ(const QDomElement &elem);
    void    parse(const QDomElement &element);
    QString getFrom()    const { return m_from; }
    QString getAppName() const { return m_app;}
    QString getTo() const { return m_to;}
    QString getid() const { return m_id;}
signals:

public slots:

protected:
    /// \cond
    void parseElementFromChild(const QDomElement &element);
    void toXmlElementFromChild(QXmlStreamWriter *writer) const;
    /// \endcond

private:
    QString     m_app;
    QString     m_to;
    QString     m_from;
    QString     m_id;
};

#endif // QAUTHIQ_H
