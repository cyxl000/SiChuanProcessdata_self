#ifndef OPENREAD_H
#define OPENREAD_H
#include<QProgressBar>
#include<QTextBrowser>
#include<QHBoxLayout>
#include<QLabel>
#include<QDockWidget>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QSpacerItem>
#include<QPushButton>


#include<QMessageBox>
#include <QDialog>
#include"monthdata.h"
#include "dealdatas.h"
#include "ratetoradia.h"
#include"Radiation.h"
#include"sunrate.h"
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
#include<QFileDialog>
//namespace Ui {
//class OpenRead;
//}

class OpenRead :public QWidget
{
    Q_OBJECT

public:
    explicit OpenRead(QWidget *parent = 0);
    ~OpenRead();
    QVector<MonthData> stdPoint;//标准点和一个月的结果 x y c c c
   // QVector<QString> filePath;//小文件路径
   // QVector<int> txtNum;//大文件夹路径

    //计算用的日照变量
    QMultiMap<double,sunRate> coEfficient;
    QVector<monthCloud> stdcCloud;//每月云量

    //计算辐射用的变量
    QMap<QString,State> state;//站点和坐标
    QMultiMap<QString,stateAdCoeffi> locateCoffi;//站点和系数
    QVector<MonthResult> monthresult;//读取并装一个月的结果



public slots:
   // void on_pushButton_clicked();

    //void on_pushButton_2_clicked();
    void stdFile();//读取标准文件
    void findtext();//找到目标文件
    void data_Processing();//stdCoordinate是对stdPoint的引用

//计算日照率用的函数
   // void on_pushButton_3_clicked();
    void readRate();
    void readCloud(QFileInfo& info1);

 //计算辐射用的函数
  // void on_pushButton_4_clicked();
   void readToRadiation();
   void readStateAnde(QString& path);
   void button1();
   void button2();
   void button3();
   void button4();
   void button5();
   void inttr(const QString&);

private:
   // Ui::OpenRead *ui;

signals:


protected:
    void run();
    dealDatas* deal;
    QProgressBar* wholeProgress1;
    QProgressBar* monthProgress1;
    QLabel* label1;
    QLabel* label2;
    QLabel* label3;
    QTextBrowser* textBrowser;
    QDockWidget* detailInfo;
    QPushButton* standard;
    QPushButton* destination;
    QPushButton* rizhao;
    QPushButton* qingxidu;
    QPushButton* radiation;


};

#endif // OPENREAD_H
