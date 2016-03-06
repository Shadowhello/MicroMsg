#ifndef QJSCORE_H
#define QJSCORE_H


#include <QObject>
#include <QWidget>
/**
 * @brief The QJSCore class
 *封装一些本地方法，供js调用
 *
 */

class QJSCore : public QObject
{
    Q_OBJECT
public:


    ~QJSCore();

    static QJSCore *ref()
    {
        static QJSCore js;
        return &js;
    }

signals:

public slots:

    void     msgBox(const QString &title,const QString &txt);
    QString  readFromFile(const QString &fn);
    void     saveData(const QString &fn,const QString &data);
    void     open(const QString &path);
    void     exec(const QString &path);
    void     open(const QString &path,const QStringList &arglist);
    void     close();
    QString  nameFromURL( QString url);

    void     sendData(QString msg);
    void     sendData(QString title,QString to ,QString body);
    void        setSoftInfo(QString info) { m_addsoft = info;}
    QString     getSoftInfo() { return m_addsoft;}

    void    setRoster();

    void        saveValue(QString key, QString value);
    QString     readValue(QString key);
    QString     getDCode();
private:
    explicit QJSCore(QObject *parent = 0);

    ///
    /// \brief 要添加的软件信息
    ///
    QString         m_addsoft;
};

#endif // QJSCORE_H
