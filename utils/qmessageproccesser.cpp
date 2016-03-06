#include "qmessageproccesser.h"

#include <QDomDocument>
#include <QDebug>

QMessageProccesser::QMessageProccesser(QObject *parent) :
    QObject(parent)
{
}

void QMessageProccesser::GetTitleMsg(const QString &msg, TitleMsg &rmsg, int &ret)
{
    QDomDocument dom;
    if ( !dom.setContent(msg) ){
        ret= Process_Fail;
    }
    QDomElement root = dom.documentElement();
    QString title = root.attribute("title","");
    QString from  = root.attribute("from","");
    QString to = root.attribute("to");
    QString body = root.firstChildElement("body").lastChild().nodeValue();


    qDebug()<<"body:"<<body;
    qDebug()<<"to:"<<to;
    if ( title.isEmpty() )
    {
        ret = Process_OK;
        title = "无标题";
        //ret= Process_Fail;
    }
    rmsg.body = body;
    rmsg.from = from;
    rmsg.to = to;
    rmsg.title = title;


}
