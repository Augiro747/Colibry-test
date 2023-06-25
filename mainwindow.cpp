#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "filechanger.h"

void MainWindow::Result(bool success)
{
    if(success)
        ui->Result->setText("Файл успешно изменён!");
    else
        ui->Result->setText("Не удалось изменить файл");
}

void MainWindow::error(QString err)
{
    ui->Result->setText(err);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    FileChanger *fchanger=new FileChanger;

    connect(this, &MainWindow::onGetFileName,fchanger,&FileChanger::onGetFileName);
    connect(fchanger, &FileChanger::Result,this,&MainWindow::Result);
    connect(this,&MainWindow::Check,fchanger, &FileChanger::Check);
    connect(fchanger, &FileChanger::error,this,&MainWindow::error);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_DialogButton_clicked()
{
    QString masks=ui->Extension->text();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr(qPrintable(masks)));
    QString outputFile=ui->OutputFilePathLabel->text()+"/"+ui->OutputExtension->text();
    bool deleteInput=ui->DeleteInput->isChecked(),rewrite=ui->RewriteFile->isChecked(),oneTime=ui->FileCheck->isChecked();
    int timer=ui->Timer->text().toInt();
    char var=ui->Variable->text().toInt();
    QString operation=ui->Operation->currentText();
    emit onGetFileName(fileName,outputFile, deleteInput,rewrite,oneTime,timer,var,operation);
}




void MainWindow::on_OutputFilePath_clicked()
{
    QString outputDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"",QFileDialog::ShowDirsOnly);
    ui->OutputFilePathLabel->setText(outputDir);
}





void MainWindow::on_FileCheck_clicked()
{
    emit Check(ui->FileCheck->isChecked());
}

