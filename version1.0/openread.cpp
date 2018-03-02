#include "openread.h"

#include<QMessageBox>
#include<QDebug>

OpenRead::OpenRead(QWidget *parent): QWidget(parent)
{
    QGridLayout* lay = new QGridLayout(this);
   // totalProgress(12,"file1");
    wholeProgress1 = new QProgressBar;
    wholeProgress1->setRange(0,100);
    wholeProgress1->setValue(0);
    monthProgress1 = new QProgressBar;
    monthProgress1->setRange(0,1000);
    monthProgress1->setValue(0);
    label1 = new QLabel;
    label1->setText("总读取进度");
    label2 = new QLabel;
    label2->setText("月读取进度");
    label3 = new QLabel;
    label3->setText("具体细节");
    standard = new QPushButton;
    standard->setText("标准文件");
    destination = new QPushButton;
    destination->setText("目标文件");
    rizhao = new QPushButton;
    rizhao->setText("日照");
    qingxidu = new QPushButton;
    qingxidu->setText("清晰度");
    radiation = new QPushButton;
    radiation->setText("辐射");


    textBrowser = new QTextBrowser(this);
    detailInfo = new QDockWidget(this);
   // QHBoxLayout* hbox = new QHBoxLayout(this);
    QHBoxLayout* h1 = new QHBoxLayout;
    QHBoxLayout* h2 = new QHBoxLayout;
    QHBoxLayout* h3 = new QHBoxLayout;
    QHBoxLayout* h4 = new QHBoxLayout;
  // h1->addItem(label1);
    h1->addWidget(label1);
   h1->addStretch();
   h2->addWidget(label2);
   h2->addStretch();
   h3->addWidget(label3);
   h3->addStretch();
   h4->addWidget(standard);
   h4->addWidget(destination);
   h4->addWidget(rizhao);
   h4->addWidget(qingxidu);
   h4->addWidget(radiation);
   h4->addStretch();
   lay->addLayout(h4,0,0);
   lay->addLayout(h1,1,0);
   lay->addWidget(wholeProgress1,2,0);
   lay->addLayout(h2,3,0);
   lay->addWidget(monthProgress1,4,0);
   lay->addLayout(h3,5,0);
   detailInfo->setWidget(textBrowser);
   lay->addWidget(detailInfo,6,0);

   connect(standard,SIGNAL(clicked(bool)),this,SLOT(button1()));
   connect(destination,SIGNAL(clicked(bool)),this,SLOT(button2()));
   connect(rizhao,SIGNAL(clicked(bool)),this,SLOT(button3()));
   connect(qingxidu,SIGNAL(clicked(bool)),this,SLOT(button4()));
   connect(radiation,SIGNAL(clicked(bool)),this,SLOT(button5()));

}

OpenRead::~OpenRead()
{
}
//目标文件
/*void OpenRead::on_pushButton_2_clicked()
{
    findtext();
}*/

void OpenRead::button1()
{
    stdFile();
}
void OpenRead::button2()
{
    findtext();
}
void OpenRead::button3()
{
    readRate();
}
void OpenRead::button4()
{
    readToRadiation();
}

void OpenRead::button5()
{
    Radiation r;
    r.readRadiation();
    r.readData();
}

void OpenRead::inttr(const QString &str)
{
    textBrowser->append(str);
}
//遍历目标文件
void OpenRead::findtext()
{
    QString str0 = "E:/FirstYGraduate/meteorology/GISCloudInfo/SiChuan";
    QDir dir0(str0);
    if (!dir0.exists())
        return ;
    dir0.setFilter(QDir::Files | QDir::Dirs);
         dir0.setSorting(QDir::NoSort);

         QFileInfoList list = dir0.entryInfoList();
         for (int i = 2; i < list.size(); ++i) {//i=2,list.size()/////////////////////////
            // dealDatas deal(stdPoint);
            // dealDatas deal(stdPoint);


             QFileInfo fileInfo = list.at(i);//
             QString dirPath = fileInfo.filePath();//找到一级目录
             QString dirname = fileInfo.fileName();

              deal = new dealDatas(stdPoint,dirPath,dirname);
             connect(deal,SIGNAL(sigstr(const QString&)),this,SLOT(inttr(const QString&)),Qt::QueuedConnection);
             //qDebug()<<"文件夹"<<fileInfo.fileName();//
          /*
             QDir dir1(dirPath);
             if (!dir1.exists())
                 return ;
             dir1.setFilter(QDir::Files);
             dir1.setSorting(QDir::NoSort);
             QFileInfoList list1 = dir1.entryInfoList();
             qDebug()<<list1.size();
            // txtNum.append(list1.size());
             emit sigR(list1.size());

             for (int j = 93; j < list1.size(); ++j) {//j=0,///////////////list1.size()
                 QFileInfo fileInfo1 = list1.at(j);//
                 QString fiPath = fileInfo1.filePath();//找到终极文件
                 qDebug()<<"文件数"<<fileInfo1.fileName();
                 //filePath.append(fiPath);
                 qDebug()<<"j="<<j;
                 */

             //开线程
             deal->start();
                 //deal->calculateSave(i-1);
               }

         }


void OpenRead::data_Processing()
{

}

//标准文件
/*void OpenRead::on_pushButton_clicked()
{
   stdFile();

}*/
//标准文件读取
void OpenRead::stdFile()
{
    QFile file("E:/FirstYGraduate/meteorology/02MediumData/010StadardPt.csv");
    qDebug()<<"读取文件";

     if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
       // QMessageBox::critical(this,"Error","文件打开错误，请重新打开",QMessageBox::Yes);
        return ;
     }
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
             double x = data.at(1).toDouble();
             double y = data.at(2).toDouble();
            MonthData monthData;
             monthData.x = x;
             monthData.y = y;
             stdPoint.append(monthData);

         }
     }
}




/*************日照百分率******************/
//
/*void OpenRead::on_pushButton_3_clicked()
{
   readRate();

}*/

void OpenRead::readRate()
{
    QString str;
    QString targetPath=QFileDialog::getExistingDirectory(NULL,"选择目标文件路径",str);
    QFileInfo info(targetPath);
    str=info.absolutePath();//添加路径，下次打开可以直接定位到所打开的目录中
    QDir dir0(targetPath);
    if (!dir0.exists())
        return ;
    dir0.setFilter(QDir::Files);
    dir0.setSorting(QDir::NoSort);
    QFileInfoList list1 = dir0.entryInfoList();
    qDebug()<<list1.size();

     //读取文件
        QFileInfo fileInfo0 = list1.at(12);//
        QString fipath = fileInfo0.filePath();
        QFile file(fipath);
         if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            //QMessageBox::critical(this,"Error","文件打开错误，请重新打开",QMessageBox::Yes);
            return ;
         }
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
                sunRate sunrate;
                double y = data.at(1).toDouble();
                sunrate.idName = data.at(0);
                sunrate.x = data.at(2).toDouble();
                sunrate.a = data.at(3).toDouble();
                sunrate.b = data.at(4).toDouble();
                coEfficient.insert(y,sunrate);
            }
      }
       // qDebug()<<"coEfficient.size()"<<coEfficient.size();


        for (int j = 0; j < list1.length()-1; ++j) {//list1.length()-1
            QFileInfo fileInfo1 = list1.at(j);
            QString filename = fileInfo1.fileName();
            readCloud(fileInfo1);


        CalculateRate calculate(coEfficient,stdcCloud);
        calculate.findLearst();
        calculate.saveFile(filename);

        //处理完一个文件后要清除
        stdcCloud.clear();
    }
}

void OpenRead::readCloud(QFileInfo &info1)
{
    QString piPath = info1.filePath();
   QFile file(piPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
       //QMessageBox::critical(this,"Error","文件打开错误，请重新打开",QMessageBox::Yes);
       return ;
    }
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
                monthCloud c1;
                c1.x = data.at(0).toDouble();
                c1.y = data.at(1).toDouble();
                c1.c = data.at(2).toDouble();
                stdcCloud.append(c1);
            }
      }
/*
    for(int i=0;i<stdcCloud.length();i++){
        qDebug()<<stdcCloud.at(i).x<<stdcCloud.at(i).y<<stdcCloud.at(i).c;
}
*/
}

//清晰度指数
/*void OpenRead::on_pushButton_4_clicked()
{
    readToRadiation();
}*/

void OpenRead::readToRadiation()
{
    QString str;
    QString targetPath=QFileDialog::getExistingDirectory(NULL,"选择目标文件路径",str);
    QFileInfo info(targetPath);
    str=info.absolutePath();//添加路径，下次打开可以直接定位到所打开的目录中
    QDir dir0(targetPath);
    if (!dir0.exists())
        return ;
    dir0.setFilter(QDir::Files);
    dir0.setSorting(QDir::NoSort);
    QFileInfoList list1 = dir0.entryInfoList();
   //读站名和系数部分
    QString AllData;
    QString lineData;
    QStringList list;
    QStringList data;
    list.clear();
    data.clear();

    QFile file(list1.at(12).filePath());//站名和坐标
    qDebug()<<"list1.at(12)"<<list1.at(12).fileName();
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
       //QMessageBox::critical(this,"Error","文件打开错误，请重新打开",QMessageBox::Yes);
       return ;
    }
    QTextStream in(&file);
        while(!in.atEnd()){
            qDebug()<<"有问题？";
            AllData = in.readAll();
            list = AllData.split("\n",QString::SkipEmptyParts);
            qDebug()<<list.size();
            for(int i=0; i<list.length(); i++){
                lineData = list.at(i);
                data = lineData.split(",",QString::SkipEmptyParts);
                State s;
                QString id = data.at(5);
                s.x = data.at(2).toDouble();
                s.y = data.at(1).toDouble();
                state.insert(id,s);
               // qDebug()<<data.at(0)<<data.at(1)<<data.at(2);
            }
      }
        qDebug()<<"站名和坐标"<<state.size();
        for( QMap<QString,State>::iterator it = state.begin(); it!=state.end();it++)//站点和坐标
        {
            State s0 = it.value();
            qDebug()<<it.key()<<s0.x<<s0.y;
        }


        QFile file1(list1.at(13).filePath());//站名和系数
        if(!file1.open(QIODevice::ReadOnly | QIODevice::Text)){
           //QMessageBox::critical(this,"Error","文件打开错误，请重新打开",QMessageBox::Yes);
           return ;
        }
        QTextStream in1(&file1);
            while(!in1.atEnd()){
                AllData = in1.readAll();
                list.clear();
                list = AllData.split("\n",QString::SkipEmptyParts);
               // qDebug()<<"length="<<list.length();
                for(int i=1; i<list.length(); i++){
                    lineData = list.at(i);
                    data = lineData.split(",",QString::SkipEmptyParts);
                    stateAdCoeffi co;
                    QString name  = data.at(0);
                    co.month = data.at(1).toInt();
                    co.a = data.at(2).toDouble();
                    co.b = data.at(3).toDouble();
                    locateCoffi.insert(name,co);
                   // qDebug()<<co.a<<co.b<<co.month;

                }
          }

       /*     qDebug()<<"站名和系数"<<locateCoffi.size();
            for(QMultiMap<QString,stateAdCoeffi>::iterator it = locateCoffi.begin(); it!=locateCoffi.end();it++){
                stateAdCoeffi c = it.value();
                qDebug()<<it.key()<<c.month<<c.a<<c.b;
            }
*/
   // qDebug()<<list1.length();

    for(int i=0; i<list1.length()-2; i++){//list1.length()-2
        QString path = list1.at(i).filePath();
       // qDebug()<<name;
         readStateAnde(path);
         RateToRadia deal(state, locateCoffi);
         deal.dealDate(monthresult,i);
         deal.saveFile(i+1);
         //每处理完一个文件就清空
         monthresult.clear();
    }
}


void OpenRead::readStateAnde(QString &path)
{
    QFile file(path);//站名和系数
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
       //QMessageBox::critical(this,"Error","文件打开错误，请重新打开",QMessageBox::Yes);
       return ;
    }
    QString AllData;
    QString lineData;
    QStringList list;
    QStringList data;
    list.clear();
    data.clear();
    QTextStream in1(&file);
        while(!in1.atEnd()){
            AllData = in1.readAll();
            list.clear();
            list = AllData.split("\n",QString::SkipEmptyParts);
           // qDebug()<<"length="<<list.length();
            for(int i=1; i<list.length(); i++){
                lineData = list.at(i);
                data = lineData.split(",",QString::SkipEmptyParts);
               MonthResult m2;
               m2.x = data.at(0).toDouble();
               m2.y = data.at(1).toDouble();
               m2.coefficient = data.at(3).toDouble();//////////////////////////data.at(4)
             //  qDebug()<<m2.x<<m2.y<<m2.coefficient;
               monthresult.append(m2);


            }
      }
        qDebug()<<monthresult.size();

}
