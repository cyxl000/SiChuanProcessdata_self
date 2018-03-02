#ifndef CLOUDAMOUNTPROCESSING_H
#define CLOUDAMOUNTPROCESSING_H
/*
 * 此类是进行云量处理的类，每次传入一个云量的路径
*/
#include<QObject>
#include<QRunnable>
#include<QThread>
#include "cloudamount.h"
#include "datastorage.h"
#include <QVector>
class cloudAmountProcessing:public QObject, public QRunnable
{
    Q_OBJECT
public:
    cloudAmountProcessing(QString& monthPath);
    //每次只需要调用process(const QString &monthPath)接口即可
    void process();
    QVector<cloudAmount> readBasicCoord(const QString &path);
    QVector<dataStorage> readBasicData(const QString &dayPath);
    void preprocessing(QVector<dataStorage> &sourceData);
    void insertAmount(const QVector<dataStorage> &rangeData,QVector<cloudAmount> &finishedData);
    void averageData(QVector<cloudAmount> &sumData);
    void writeCLoud(const QVector<cloudAmount> &finalData,
                    const QString &fileName,
                    const QString &valueName);
    void run();
    //标准坐标最大、最小的X值
    double minStandardX;
    double maxStandardX;

    double minXBoundary;
    double maxXBoundary;
    double minYBoundary;
    double maxYBoundary;
    QString monthPath;
};

#endif // CLOUDAMOUNTPROCESSING_H
