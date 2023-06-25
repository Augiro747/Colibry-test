#ifndef FILECHANGER_H
#define FILECHANGER_H

#include <QObject>
#include <QFile>
#include <QTimer>
#include <QTime>

class FileChanger : public QObject
{
    Q_OBJECT

    QByteArray qba;
    QTimer checkTimer;
    QString iFileName,oFileName,operation;
    int timerInterval;
    char var;
    bool fRewrite, stopCheck=false;

public:
    explicit FileChanger(QObject *parent = nullptr);

signals:
    void Result(bool success);
    void error(QString err);

public slots:
    void onGetFileName(QString inputFile,QString outputFile, bool deleteInput, bool rewrite,bool oneTime, int timer,char variable,QString changeType);
    void Check(bool chk);

private slots:
    void TimerCheck();

private:
    void DeleteFile(QString fileName);
    void SaveFile();
    void ChangeData();
};

#endif // FILECHANGER_H
