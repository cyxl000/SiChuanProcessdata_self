#ifndef CLOUDAMOUNT_H
#define CLOUDAMOUNT_H
/*
 * 这个类是将所有的云量数据对应到Xcoord，YCoord，存起来的类
 * 用来存储求平均时的每一个云量数据
*/
#include <QVector>
class cloudAmount
{
public:
    double XCoord;
    double YCoord;
    QVector<double> Clouds;
};

#endif // CLOUDAMOUNT_H
