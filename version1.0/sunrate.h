#ifndef SUNRATE_H
#define SUNRATE_H
#include"monthdata.h"
#include<QString>
#include<QVector>
#include<QMultiMap>
#include<QDebug>
#include<QFile>
#include<QDir>
class sunRate
{
public:
    double x;
    QString idName;
    double a;
    double b;

};
class CalculateRate
{
public:
    CalculateRate(QMultiMap<double,sunRate>, QVector<monthCloud>);
    void findLearst();
    void saveFile(QString);
private:
    QMultiMap<double,sunRate> stdcloud;
    QVector<monthCloud> readCloud;
};
#endif // SUNRATE_H

