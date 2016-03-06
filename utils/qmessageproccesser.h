#ifndef QMESSAGEPROCCESSER_H
#define QMESSAGEPROCCESSER_H

#include "utils/defines.h"

#include <QObject>

class QMessageProccesser : public QObject
{
    Q_OBJECT
public:
    explicit QMessageProccesser(QObject *parent = 0);
    ~QMessageProccesser(){}

    /**
     * @brief GetTitleMsg
     * @param msg
     * @param rmsg
     * @param ret 0 :ok  -1: fail
     */
    void  GetTitleMsg(const QString &msg, TitleMsg &rmsg,int &ret);


signals:

public slots:

};

#endif // QMESSAGEPROCCESSER_H
