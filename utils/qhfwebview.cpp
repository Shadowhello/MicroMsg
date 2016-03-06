#include "qhfwebview.h"
#include "jsCore/qjscore.h"


#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QPalette>
#include <QMouseEvent>
#include <QWebSettings>
#include <QWebFrame>
#include <QNetworkReply>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>
#include <QProcess>
#include <QDir>

#include <Windows.h>
#include <ShellAPI.h>
#include <QMouseEvent>

QHFWebView::QHFWebView(QWidget *parent) : QWebView(parent),m_filepath("html/files"),m_bfinished(false)
{
    this->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}

void QHFWebView::mouseDoubleClickEvent(QMouseEvent *evt)
{
    evt->ignore();
}

void QHFWebView::setTransparent(bool )
{
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Base,Qt::transparent);

    this->page()->setPalette(palette);
    setAttribute(Qt::WA_OpaquePaintEvent,false);
}

void QHFWebView::registerObject()
{
    QJSCore *core = QJSCore::ref();
    page()->mainFrame()->addToJavaScriptWindowObject("Qt",core);
}

void QHFWebView::load(const QUrl &url)
{
    QWebView::load(url);
    QWebSettings *sets = this->page()->settings();
    sets->setAttribute(QWebSettings::JavascriptEnabled,true);
    sets->setAttribute(QWebSettings::LocalContentCanAccessFileUrls,true);
    sets->setAttribute(QWebSettings::LocalStorageEnabled,true);
    connect(page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(registerObject()));
}
void QHFWebView::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    QWebView::mousePressEvent(e);
}
void QHFWebView::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
    QWebView::mouseMoveEvent(e);
}

void QHFWebView::mouseReleaseEvent(QMouseEvent *e)
{
    QWidget::mouseReleaseEvent(e);
    QWebView::mouseReleaseEvent(e);
}
