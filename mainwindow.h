#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void onGetFileName(QString inputFile,QString outputFile, bool deleteInput, bool rewrite,bool oneTime, int timer,char variable,QString changeType);
    void Check(bool chk);

public slots:
    void Result(bool success);
    void error(QString err);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_DialogButton_clicked();
    void on_OutputFilePath_clicked();

    void on_FileCheck_clicked();

private:
    Ui::MainWindow *ui;
    QString masks;
};
#endif // MAINWINDOW_H
