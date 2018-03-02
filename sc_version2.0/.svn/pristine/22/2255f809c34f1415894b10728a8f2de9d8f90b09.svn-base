#ifndef READANDWRITE_H
#define READANDWRITE_H
/*
 * 这个类是将读数据和写数据独立拿出来的类
 * readFiles()是将readfilePath里边的文件夹路径中的文件路径读出来
 *
 * writeFile()是将处理完了的x,y,value三个数据读取到指定的文件夹中
 * （输入为一个存储文件的文件夹名称，一个上述三个数据的容器，一个value的标签（如：sunshineRate、clarity..））
*/
#include <QString>
#include <QStringList>
#include "datastorage.h"
#include <QVector>
class readAndWrite
{
public:
    readAndWrite();
    //通过文件夹的路径遍历出里边的文件，对于只需要一个文件夹的就只用判断该目录下文件的个数是否为1即可，不是1就报错
    QStringList readFiles(const QString &dirPath);
    //再添加一个读入三个数据函数,输入为路径
    QVector<dataStorage> readData(const QString &filePath);
    //这里传入的是参数是：要写的数据、所装入的文件夹的名字、文件的名字、所对应的value的名字
    void writeFile(const QVector<dataStorage> &finalData,
                   const QString &dirName,
                   const QString &fileName,
                   const QString &valueName);
};

#endif // READANDWRITE_H
