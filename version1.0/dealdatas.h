#ifndef DEALDATAS_H
#define DEALDATAS_H
#include"monthdata.h"
#include<QFile>
#include<QDebug>
#include<QFileInfo>
#include<QDir>
#include<QMultiMap>
#include<QMap>
#include<QVector>
#include<QTextStream>
#include<QString>
#include<QStringList>
#include<QMessageBox>
#include<QThread>

class dealDatas:public QThread
{
    Q_OBJECT
public:
    dealDatas(QVector<MonthData>&,QString,QString);
   // void setVal();
    void readData();
    void sortData(QMultiMap<double,QVector<double> >&txtData);
    void processSortD(QMap<double, QVector<double> >&sortD);
    double findC(QVector<double>&,QVector<double>&);
    double refind(QVector<double>&);
    void calculateSave(QString);
    void run();

public:
    QString dirPath;
    QString dirname;
    QVector<MonthData> monthData;//monthData是一个月的y,x,cccc和前面的stdPoint是同一个
    //QMultiMap<double,QVector<double> >txtData;//一个文件的数据并排序,排完序之后可清空
    //QMap<double, QVector<double> >sortD;
signals:
    void sigstr(const QString&);
};

#endif // DEALDATAS_H
