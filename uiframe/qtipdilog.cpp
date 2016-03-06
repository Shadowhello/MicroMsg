#include "qtipdilog.h"
#include "utils/qapputils.h"

#include <QVBoxLayout>
#include <QWebFrame>

static QHash<QString,QDateTime>        m_app_hist;

QTipDilog::QTipDilog(QWidget *parent) :
    QDialog(parent)
{
    initUI();
//    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//    setAttribute(Qt::WA_TranslucentBackground);
//    showFullScreen();
    resize(800,500);
    //setAttribute(Qt::WA_ShowModal);
    setVisible(false);
}


void QTipDilog::initUI()
{
    QWidget     *center = new QWidget(this);
    QVBoxLayout *vlay   = new QVBoxLayout(center);
    QVBoxLayout *main = new QVBoxLayout(this);

    vlay->setMargin(0);
    main->setMargin(0);
    center->setAttribute(Qt::WA_TranslucentBackground);
    m_web = new QHFWebView(center);

    connect(m_web->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(regObject()));

    m_web->load(QUrl("html/verify.html"));
    m_web->setTransparent(true);
    vlay->addWidget(m_web);
    main->addWidget(center);

}

void QTipDilog::setYes(QString)
{
    QString app = m_iqproc->getAppName();
    if ( !m_app_hist.contains(app))
    {
        m_app_hist[app] = QDateTime::currentDateTime();
    }

    m_iqproc->sendYes(m_client);
    setVisible(false);
}
void QTipDilog::setNo(QString)
{
    m_iqproc->sendNo(m_client);
    setVisible(false);
}
void QTipDilog::exec()
{
    //resize(800,700);

    QString app = m_iqproc->getAppName();
    if( !m_app_hist.contains(app) )
    {

    }else {
        QDateTime t = m_app_hist[app];

        if ( t.secsTo(QDateTime::currentDateTime()) < VALID_TIME )
        {
            setYes("");
            m_app_hist[app] = QDateTime::currentDateTime();
            qDebug()<<"Reset Login Time";
            return;
        }else{
            m_app_hist[app] = QDateTime::currentDateTime();
            qDebug()<<"Reset Login Time";
        }

    }

    QDialog::exec();
}

void QTipDilog::setIQProc(QIQProcesser *iq)
{
    m_iqproc = iq;
    QString js;
    js = "$(document).setApp('"+iq->getAppName() +"')";
    qDebug()<<js;
    m_web->page()->mainFrame()->evaluateJavaScript(js);
    js = "$(document).setFrom('" + iq->getFrom() + "')";
    qDebug()<<js;
    m_web->page()->mainFrame()->evaluateJavaScript(js);
}

void QTipDilog::regObject()
{
    m_web->page()->mainFrame()->addToJavaScriptWindowObject("Tip",this);
}
