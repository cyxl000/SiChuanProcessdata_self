#ifndef READFILEPATH_H
#define READFILEPATH_H
/*此类是专门用于从配置文件里边读取输入和的路径的类，
 * 将 基本经纬度坐标、开阔度结果、清晰度系数表格、日照系数表格、云量基础数据
 * 的路径
*/
#include <QCoreApplication>
#include <QString>
#include <QStringList>
class ReadFilePath
{
public:
    ReadFilePath();
    //基准坐标表路径
    static QString baseCoordPath;
    //开阔度路径
    static QString kaiKuoDuPath;
    //清晰度系数路径
    static QString clarityFactorsPath;
    //日照系数路径
    static QString sunRateFactorsPath;
    //基础云量数据路径
    static QString basicCloudPath;
    //结果放置路径
    static QString consequencePath;
    //所开线程个数
    static int threadNum;
};

#endif // READFILEPATH_H
