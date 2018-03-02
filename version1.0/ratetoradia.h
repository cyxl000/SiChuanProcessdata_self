#ifndef RATETORADIA_H
#define RATETORADIA_H
#include<QString>
#include<QMultiMap>
#include<QMap>
#include<QVector>
#include<QDebug>
#include<QString>
#include<QTextStream>
class State{//站名和坐标
public:
    double x;
    double y;
};
class stateAdCoeffi{//放在Multimap中值的位置
    //QString idName;
public:
    int month;
    double a;
    double b;
};
class MonthResult{
public:
    QString idName;
    double coefficient;
    double x;
    double y;
    double radiation;
};

class RateToRadia
{
public:
    RateToRadia( QMap<QString,State>state,QMultiMap<QString,stateAdCoeffi> locateCoffi);
    void dealDate(QVector<MonthResult> &monthresult, int);
    void saveFile(int);

private:
    QMap<QString,State> state;//站点和坐标
    QMultiMap<QString,stateAdCoeffi> locateCoffi;//站点和系数
    QVector<MonthResult> result;
};

#endif // RATETORADIA_H
