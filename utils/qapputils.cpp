#include "qapputils.h"
#include "utils/defines.h"

#include <QFileInfo>
#include <QFileIconProvider>
#include <QDesktopWidget>
#include <QFile>
#include <QSettings>
#include <QApplication>

QAppUtils::QAppUtils(QObject *parent) : QObject(parent)
{

}

QSize QAppUtils::getScreenSize(int i)
{
    QDesktopWidget *desk = QApplication::desktop();
    QRect rt = desk->screenGeometry(i);

    return QSize(rt.width(),rt.height());
}

void QAppUtils::getScreenSize(int &wid, int &hei)
{
    QSize sz = getScreenSize();
    wid = sz.width();
    hei = sz.height();
}

void QAppUtils::getWorkAreaSize(int &wid, int &hei)
{
    QDesktopWidget *desk = QApplication::desktop();
    QRect rt = desk->availableGeometry();
    wid = rt.width();
    hei = rt.height();
}

int QAppUtils::getTaskBarHeight()
{
    int wid,wh,hei;
    hei = getScreenHei();
    getWorkAreaSize(wid,wh);
    return hei - wh;
}

int QAppUtils::getScreenWid(int i)
{
   QSize sz = getScreenSize(i);
   return sz.width();
}

int QAppUtils::getScreenHei(int i)
{
    QSize sz = getScreenSize(i);
    return sz.height();
}

void QAppUtils::getAppList(QHash<QString, QString> &mapapp)
{

}


QPixmap& QAppUtils::getAppIcon(const QString &path)
{
    QFileInfo info(path);
    QFileIconProvider prod;
    QIcon icon =  prod.icon(info);
    static QPixmap pix;
    pix = icon.pixmap(40,40);
    return pix;

}
