#include "readandwrite.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QFileInfoList>
#include "readfilepath.h"
#include <QDebug>
#include <QMessageBox>
readAndWrite::readAndWrite()
{

}
QStringList readAndWrite::readFiles(const QString &dirPath)
{
    QStringList pathList;
    QDir dir(dirPath);
    qDebug()<<dirPath;
    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Dirs |QDir::Files | QDir::NoDotAndDotDot);
    foreach (QFileInfo fileInfo, fileInfoList)
    {
       QString filePath = fileInfo.absoluteFilePath();
       pathList.append(filePath);
    }
    return pathList;
}
QVector<dataStorage> readAndWrite::readData(const QString &filePath)
{
    QVector<dataStorage> myData;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    QMessageBox::information(NULL,"error!","所读取路径错误，无法打开文件\n"+filePath);
    QTextStream out(&file);
    QString tmp = out.readLine();
    qDebug()<<tmp;
    while (!out.atEnd())
    {
        QString line = out.readLine();
        QStringList ele = line.split(",");
        QString x = ele.at(0);
        QString y = ele.at(1);
        QString v = ele.at(2);
        dataStorage myLine;
        myLine.XCoord = x.toDouble();
        myLine.YCoord = y.toDouble();
        myLine.myValue = v.toDouble();
        myData.append(myLine);
    }
    file.close();
    return myData;
}
void readAndWrite::writeFile(const QVector<dataStorage> &finalData,
                             const QString &dirName,
                             const QString &fileName,
                             const QString &valueName)
{
    QDir dir(ReadFilePath::consequencePath);
    dir.mkdir(dirName);
    dir.cd(dirName);
    QString filePath = dir.absolutePath() + "/" +fileName;
    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream in(&file);
    in << "XCoord,YCoord," << valueName << endl;
    for(int i = 0;i < finalData.length();i++)
    {
        in << finalData.at(i).XCoord << "," << finalData.at(i).YCoord <<
              "," <<finalData.at(i).myValue <<endl;
    }
    file.close();
}
