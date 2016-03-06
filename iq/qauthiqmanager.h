#ifndef QAUTHIQMANAGER_H
#define QAUTHIQMANAGER_H

#include "uiframe/qtipdilog.h"

#include <QObject>

#include <QXmppClientExtension.h>

class QAuthIQManager : public QXmppClientExtension
{
    Q_OBJECT
public:
    QAuthIQManager();
    ~QAuthIQManager();
    bool handleStanza(const QDomElement &stanza);
signals:

    void    show_tips_sig(QString from,QString to,QString app,QString id);
public slots:
    void    show_tips(QString from,QString to,QString app,QString id);

private:
    QTipDilog   *tip;
};

#endif // QAUTHIQMANAGER_H
