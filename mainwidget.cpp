#include "mainwidget.h"
//#include "ui_mainwidget.h"
#include "utils/qhfwebview.h"

#include "utils/defines.h"
#include "login/session.h"

#include <QSettings>

#include <QMouseEvent>
#include<QHBoxLayout>
#include <QDebug>
#include <QWebFrame>
#include <QTextCodec>
#include <QApplication>
#include <QMenu>

#include "md5/md5.h"

//c lib
#include "ipc/cnamedpiple.h"

#define     PIPE_NAME       "\\\\.\\Pipe\\caizheng"

#ifdef __cplusplus
extern "C"{
#endif

MemPool     *mpool;
static char* check(const char* usr, const char* rnd)
{
    char *res = (char*)m_malloc( mpool );
    char key[] = "77@hf-soft";
    MD5 md5;

    strcpy(res,usr);
    strcat(res,rnd);
    strcat(res,key);

    md5.update(res);
    strcpy(res,md5.toString().c_str());

    return res;
}

static void*    Pipe_Server(void* arg)
{
    mpool = pool_create(256,100);
    while (1)
    {
        CNamedPiple *pipe = new CNamedPiple(PIPE_NAME);
        char        *hash, rnd[10] = {0},*realhash;

        if ( pipe->ConnectPipe())
        {
            qDebug()<<"Pipe Connected";
            pipe->SendData((const char*)arg);
            sprintf(rnd,"%d",rand()%1000000000);
            pipe->SendData(rnd);
            hash = pipe->ReadData();
            qDebug()<<"Recv Hash:"<<hash;
            realhash = check((char*)arg,rnd);
            qDebug()<<"Real Hash is:"<<realhash;
            if ( strcmp(hash,realhash))
            {
                pipe->SendData("No");
            }else
            {
                pipe->SendData("Yes");
            }
            m_free(mpool,(void**)&realhash);
        }
        pipe->Close();
        delete pipe;
        qDebug()<<(char*)arg;
    }
}

#ifdef __cplusplus
}
#endif


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)/*,
    ui(new Ui::MainWidget)*/
{
    //ui->setupUi(this);
    initUI();
    resize(1000,700);
    setWindowFlags(Qt::FramelessWindowHint);

    m_timer = new QTimer(this);
    m_timer->setInterval(600);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(flashIcon()));
}

void MainWidget::start()
{
    m_timer->start();
}
void MainWidget::stop()
{
    m_timer->stop();
    m_tray->setIcon(QIcon("html/images/user.png"));
}

void MainWidget::initUI()
{
    QHBoxLayout *mainLay = new QHBoxLayout(this);
    QWidget *center = new QWidget(this);
    QHBoxLayout *lay = new QHBoxLayout(center);
    Task        *task = new Task;
    char        *usr = (char*)malloc(sizeof(char)*64);

    lay->setMargin(0);
    mainLay->setMargin(0);
    m_web = new QHFWebView(this);

    connect(m_web->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addObject()));
    m_web->load(QUrl("html/super.html"));
    lay->addWidget(m_web);
    mainLay->addWidget(center);

    m_tray = new QSystemTrayIcon(this);
    m_tray->setIcon(QIcon("html/images/user.png"));
    connect(m_tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(activated(QSystemTrayIcon::ActivationReason)));
    QMenu *menu = new QMenu(this);
    setCharset("GBK");
    QAction *action = new QAction("退出",this);
    connect(action,SIGNAL(triggered()),this,SLOT(close()));
    menu->addAction(action);
    m_tray->setContextMenu(menu);
    setCharset("UTF-8");
    //start up pipe server
    m_thpool = thpool_create(1);
    task->fn = Pipe_Server;
    strcpy(usr,Session::Instance()->getJID().toLocal8Bit().data());
    task->arg = usr;
    add_Task(m_thpool,task);


}
void MainWidget::setCharset(QString cset)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName(cset.toAscii().data()));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(cset.toAscii().data()));
    QTextCodec::setCodecForTr(QTextCodec::codecForName(cset.toAscii().data()));
}

void MainWidget::mousePressEvent(QMouseEvent *evt)
{
    if(evt->button() != Qt::LeftButton)
    {
        m_pressed = false;
    }
    else
    {
        m_pressed = true;
        m_movePoint = evt->globalPos()-pos();
    }
}
void MainWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_pressed = false;
    update();
}
void MainWidget::mouseMoveEvent(QMouseEvent *evt)
{
    if ( m_pressed)
    {
        move(evt->globalPos() - m_movePoint);
    }
    update();
}
void MainWidget::SpecialMessage(QString title, QString from, QString body)
{
    qDebug()<<"title:"<<title<<" body:"<<body;
    QString js = "$(document).addMsg('" + title + "','" + from + "','"+body + "');";
    m_web->page()->mainFrame()->evaluateJavaScript(js);
    start();
}

void MainWidget::addObject()
{
    m_web->page()->mainFrame()->addToJavaScriptWindowObject("Main",this);
}

MainWidget::~MainWidget()
{
    QSettings set;
    set.setValue("login_usr","");
}

void MainWidget::activated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::DoubleClick:
    {
        show();
        stop();
        break;
    }
    }
}

void MainWidget::toTray()
{
    setCharset("GBK");
    QString   tips("财政U盾通");

    qDebug()<<tips;
    m_tray->setToolTip(tips);
    m_tray->show();
    m_tray->showMessage("U盾通","双击可打开主页面");

    setCharset("UTF-8");
}

void MainWidget::flashIcon()
{
    static int tms = 0;
    ++tms;
    if ( tms % 2 == 0)
    {
        m_tray->setIcon(QIcon());
    }else
    {
        m_tray->setIcon(QIcon("html/images/user.png"));
    }
    if ( tms >= 10000)
    {
        m_tray->setIcon(QIcon("html/images/user.png"));
    }
}
