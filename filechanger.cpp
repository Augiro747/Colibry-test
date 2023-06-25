#include "filechanger.h"

FileChanger::FileChanger(QObject *parent)
    : QObject{parent}
{
    connect(&checkTimer,&QTimer::timeout,this,&FileChanger::TimerCheck);
}

void FileChanger::onGetFileName(QString inputFile, QString outputFile, bool deleteInput, bool rewrite, bool upTimer, int timer,char variable,QString changeType)
{
    QFile input(inputFile);
    if(!input.open(QIODevice::ReadOnly))
    {
        //If file cant be open
        emit error("Файл не существует");
        return;
    }
    if(!input.isReadable())
    {
        //If file cant be read
        emit error("Файл не может быть прочитан");
        input.close();
        return;
    }
    //Reading to QByteArray
    qba=input.readAll();
    input.close();

    //initiation of private variables
    iFileName=inputFile;
    oFileName = outputFile;
    timerInterval=timer;
    fRewrite=rewrite;
    var=variable;
    operation=changeType;

    //Delete input file
    if(deleteInput)
        DeleteFile(inputFile);

    //If timer is enabled
    stopCheck=upTimer;
    if(upTimer)
    {
        emit TimerCheck();
    }
    else
    {
        ChangeData();
        SaveFile();
    }

    emit Result(true);
}

void FileChanger::Check(bool chk)
{
    stopCheck=chk;
}

void FileChanger::TimerCheck()
{
    QFile file(iFileName);
    if(file.exists()&&stopCheck)
    {
        checkTimer.start(timerInterval);
        ChangeData();
        SaveFile();
        return;
    }
    if(!file.exists())
        emit error("Входной файл не найден");
}

void FileChanger::ChangeData()
{
    for(int i=0;i<qba.length();i++)
    {
        if(operation=="OR")
        qba[i]=qba[i]|var;
        if(operation=="AND")
        qba[i]=qba[i]&var;
        if(operation=="XOR")
        qba[i]=qba[i]^var;
    }
}

void FileChanger::SaveFile()
{
    QFile output(oFileName);
    //If rewrite is enabled
    if(fRewrite)
    {
        if(output.exists())
            DeleteFile(oFileName);
        output.open(QIODevice::ReadWrite);
        output.write(qba);
        output.close();
    }
    else
    {
        int fileNum=0;
        QString outputForm=oFileName;
        while(output.exists())
        {
            fileNum++;
            outputForm=oFileName;
            //Search of '.' symbol to insert number there
            outputForm.insert(oFileName.lastIndexOf('.'),QString::number(fileNum));
            output.setFileName(outputForm);
        }
        output.open(QIODevice::ReadWrite);
        output.write(qba);
        output.close();
    }
}

void FileChanger::DeleteFile(QString fileName)
{
    QFile file(fileName);
    file.remove();
}



