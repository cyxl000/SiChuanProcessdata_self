#ifndef MONTHDATA_H
#define MONTHDATA_H
#include<QVector>
class MonthData{
public:
    double x;
    double y;
    QVector<double> cloud;
    MonthData& operator =(const MonthData &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->cloud = other.cloud;
        return *this;
    }

};

class monthCloud{//用于输出和读取
public:
    double x;
    double y;
    double c;
    double idName;
    double rate;
};
#endif // MONTHDATA_H
