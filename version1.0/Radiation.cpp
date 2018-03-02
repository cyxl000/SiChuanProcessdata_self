#include "Radiation.h"
#include<QDebug>
#include<math.h>
#define PI 3.1415926535897931
double Radiation::chiwei[12] = { -20.92, -12.95, -2.42, 9.41, 18.79, 23.09, 21.18, 13.45, 2.22, -9.6, -18.91, -23.05 };
double Radiation::rxs[12] = { 17, 47, 75, 105, 135, 162, 198, 228, 258, 288, 318, 344 };
int Radiation::daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};

Radiation::Radiation()
{
    str =  "E:/FirstYGraduate/meteorology/allData/Radiation/";
    //readRadiation();
   // readData();
    //qDebug()<<sizeof(float);
    //qDebug()<<sizeof(double);
}

//读取开阔度和坐标，仅读一次
void Radiation::readRadiation()
{
    qDebug()<<"readRadiation()";
    QFile f("E:/FirstYGraduate/meteorology/02MediumData/011 开阔度数据.csv");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
       QMessageBox::critical(this,"Error","文件打开错误，请重新打开",QMessageBox::Yes);
       return ;
    }
    //qDebug()<<fiPath;
   //读取数据
    QString AllData;
    QString lineData;
    QStringList list;
    QStringList data;
    list.clear();
    QTextStream in(&f);
    while(!in.atEnd()){
        AllData = in.readAll();
        list = AllData.split("\n",QString::SkipEmptyParts);
        for(int i=1; i<list.length(); i++){
            lineData = list.at(i);
            data = lineData.split(",",QString::SkipEmptyParts);
            double x = data.at(1).toDouble();
            double y = data.at(2).toDouble();
            double k = data.at(3).toDouble();
            radiationData m;
            m.x = x;
            m.y = y;
            m.kt = k;
            monthRd.append(m);
        }
    }
}


//读取每月的清晰度数据
void Radiation::readData()
{
    qDebug()<<"readData()";
    QDir dir("E:/allData/ClarityFinalData");
    if (!dir.exists())
        return ;
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::NoSort);
    QFileInfoList list1 = dir.entryInfoList();
    qDebug()<<list1.size();
    QString name="";
    for (int j = 0; j <list1.size(); ++j) {///// list1.size()
        QFileInfo fileInfo1 = list1.at(j);
        QString fiPath = fileInfo1.filePath();//找到终极文件
        name = fileInfo1.fileName();
        QString savePath = str+name;
        //读取文件
        QFile file(fiPath);
         if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::critical(this,"Error","文件打开错误，请重新打开",QMessageBox::Yes);
            return ;
         }
         //qDebug()<<fiPath;
        //读取数据
         QString AllData;
         QString lineData;
         QStringList list;
         QStringList data;
         list.clear();
         QTextStream in(&file);
         while(!in.atEnd()){
             AllData = in.readAll();
             list = AllData.split("\n",QString::SkipEmptyParts);
             for(int i=1; i<list.length(); i++){
                 lineData = list.at(i);
                 data = lineData.split(",",QString::SkipEmptyParts);
                 double clarity = data.at(2).toDouble();
                 monthRd[i-1].clarity = clarity;
                }
            }

        //计算
             TWradiation(j);
             saveFile(savePath);

         }
    saveYear();


  /*  qDebug()<<monthRd.size();
    for(int i=0;i<monthRd.size();i++){
        qDebug()<<monthRd[i].x<<monthRd[i].y<<monthRd[i].clarity<<monthRd[i].kt;
    }
    */
}
//计算
void Radiation::TWradiation(int& month)
{
    qDebug()<<"TWradiation(int& month)";
    for(int n=0;n<monthRd.size();n++){

        double clar = monthRd[n].clarity;
        double latitude = monthRd[n].y;
        double dayLength = 24*3600;
        double I0 = 1367;
        double tag = PI/180;
        //月天文辐射量
        double Q[12] = {0};
        //中间变量
        double middle[12] = {0};
        //日末时角
        double omega[12] = {0};
        //日地距离
        double sunearth[12] = {0};

        //计算各月天文辐射量等
         for (int i = 0; i < (sizeof(rxs)/8); i++)
         {
           // qDebug()<<sizeof(rxs)/8;
            omega[i] = acos(-(tan(latitude * tag) * tan(chiwei[i] * tag))) / tag;
            sunearth[i] = 1 + 0.033 * (cos(PI * 2 * rxs[i] / 365));
            middle[i] = omega[i] * tag * sin(latitude*tag) * sin(chiwei[i]* tag) +cos(latitude*tag) * cos(chiwei[i]*tag) * sin(omega[i]*tag);
            Q[i] = daysInMonth[i] * ((dayLength / PI) * I0 * middle[i]) * sunearth[i] / 1000000;
         }
            double A = 0.0;
            if (clar <= 0.8)
            {
                if (omega[month] <= 81.4)
                    A = -0.391 + 3.56 * clar - 4.189 * clar * clar + 2.137 * clar * clar * clar;
                else
                    A = -0.311 + 3.022 * clar - 3.427 * clar * clar + 1.821 * clar * clar * clar;
            }
            else if (clar > 0.8)
            {
                A = 0.825;
            }
            else{}
            //计算出水平面月平均总辐射
           // qDebug()<<"TWradiation(int& month)";
            double t = monthRd[n].radiation = clar * Q[month];
            monthRd[n].dirRadiation = clar * Q[month] * A;
            monthRd[n].irrRadiation = clar * Q[month] * (1 - A);
            double k = monthRd[n].kt;
            double endRadiation = t*k;
            monthRd[n].endRadiation = endRadiation;
            double total = monthRd[n].yearRadiation;
            monthRd[n].yearRadiation = total+endRadiation;

           // qDebug()<<monthRd[n].radiation;
    }
}

void Radiation::saveFile(QString &path)
{
    qDebug()<<"保存文件";
    QFile file(path);
    QTextStream out(&file);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QString Ra = "总辐射";
    QString dr = "直接辐射";
    QString ir = "散射辐射";
    QString er = "修正辐射";

    out<<"XCoord"<<","<<"YCoord"<<","<<Ra<<","<<dr<<","<<ir<<","<<er<<"\n";
    for(int i=0;i<monthRd.length();i++){
        out<<monthRd[i].x<<","<<monthRd[i].y<<","<<QString::number(monthRd[i].radiation,'f',16)<<","
          <<QString::number(monthRd[i].dirRadiation,'f',16)<<","<<QString::number(monthRd[i].irrRadiation,'f',16)
         <<","<<QString::number(monthRd[i].endRadiation,'f',16)<<"\n";
    }
    qDebug()<<"end";
}

void Radiation::saveYear()
{
    QString path = str+"YearRadiation.csv";
    QFile file(path);
    QTextStream out(&file);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QString yr = "年总辐射";
    out<<"XCoord"<<","<<"YCoord"<<","<<yr<<"\n";
    for(int i=0;i<monthRd.length();i++){
        out<<monthRd[i].x<<","<<monthRd[i].y<<","<<QString::number(monthRd[i].yearRadiation,'f',16)<<"\n";
    }
    qDebug()<<"yearend";
}



