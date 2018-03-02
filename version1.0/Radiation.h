#ifndef RADIATION_H
#define RADIATION_H
#include<QDialog>
#include<QVector>
#include<QFileInfo>
#include<QFileInfoList>
#include<QFile>
#include<QDir>
#include<QMessageBox>
class radiationData
{
public:
    double x;
    double y;
    double clarity;
    double kt;//开阔度
    double radiation;//总辐射
    double endRadiation;//乘以开阔度之后的辐射
    double yearRadiation=0.0;
    double dirRadiation;//直接辐射
    double irrRadiation;//散射
};



class Radiation : public QDialog
{
public:
    Radiation();
    void readData();//读取每个月的清晰度数据
    void readRadiation();//读取开阔度和坐标数据
    void TWradiation(int &month);
    void saveFile(QString& path);
    void saveYear();
private:
    QVector<radiationData> monthRd;//月辐射结果
    //赤纬
    static double chiwei[12];
    //日序数
    static double rxs[12];
    //月日数
    static int daysInMonth[12];
    QString str;

};


#endif // RADIATION_H
