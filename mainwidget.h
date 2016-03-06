#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QTimer>

#include "thpool.h"



namespace Ui {
class MainWidget;
}

class QHFWebView;
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    QHFWebView  *getWebView() { return m_web;}

    void    start();
    void    stop();
protected:
    void    initUI();
    void     setCharset(QString);
    void     mousePressEvent(QMouseEvent*);
    void     mouseReleaseEvent(QMouseEvent*);
    void     mouseMoveEvent(QMouseEvent*);
public slots:
    void    SpecialMessage(QString title,QString from,QString body);
    void    addObject();
    void    toTray();
    void    activated( QSystemTrayIcon::ActivationReason reason);

    void    flashIcon();
private:
    //Ui::MainWidget *ui;
    QHFWebView      *m_web;
    QSystemTrayIcon *m_tray;
    QPoint          m_presssPoint;
    QPoint          m_movePoint;
    bool            m_pressed;
    QTimer          *m_timer;
    thPool          *m_thpool;

};

#endif // MAINWIDGET_H
