#include "dealdatas.h"
#include<QDebug>
#include<QDateTime>

dealDatas::dealDatas(QVector<MonthData>& monthdata,QString dirPath,QString dirname)
{
   this->monthData = monthdata;
    this->dirPath = dirPath;
    this->dirname = dirname;
}


void dealDatas::readData()
{
   // QVector<MonthData>& monthdata = monthData;
    QDir dir1(dirPath);
    if (!dir1.exists())
        return ;
    dir1.setFilter(QDir::Files);
    dir1.setSorting(QDir::NoSort);
    QFileInfoList list1 = dir1.entryInfoList();
    qDebug()<<list1.size();
   // txtNum.append(list1.size());
    //emit sigR(list1.size());

    for (int j = 0; j < list1.size(); ++j) {//j=0,list1.size()///////////////list1.size()
        QFileInfo fileInfo1 = list1.at(j);//
        QString fiPath = fileInfo1.filePath();//找到终极文件
        QMultiMap<double,QVector<double> >txtData;
        qDebug()<<"文件数"<<fileInfo1.fileName();
        QString name = fileInfo1.fileName();
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss dddd");
        QString infostr = dirname+"月"+name+"---"+time+"---"+"正在处理";
        emit sigstr(infostr);
        //filePath.append(fiPath);
        qDebug()<<"j="<<j;
        QFile file(fiPath);
        qDebug()<<"读取目标文件";

         if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"文件打开错误，请重新打开";
            return ;
         }
         QString lineData;
         QStringList list;
         list.clear();
         QTextStream in(&file);
         while(!in.atEnd()){
             lineData = in.readLine();
             list = lineData.split(",",QString::SkipEmptyParts);
             double y = list.at(0).toDouble();
             double x = list.at(1).toDouble();
             double c = list.at(2).toDouble();
             if(y<35 && y>25){//
                 QVector<double>XC;
                 XC.push_back(x);
                 XC.push_back(c);
                 txtData.insert(y,XC);
             }
             else continue;

         }
         qDebug()<<"txtData的长度"<<txtData.size();
         sortData(txtData);

      }
    calculateSave(dirname);

}

void dealDatas::sortData( QMultiMap<double,QVector<double> >&txtData)
{/*
    qDebug()<<"yanzhneg";
    QMultiMap<double,QVector<double> >::iterator iy;
    for(iy=txtData.begin();iy!=txtData.end();iy++){
         qDebug()<<iy.key()<<iy.value();
    }
*/
    QMap<double, QVector<double> >sortD;
    if(!txtData.isEmpty())
    {
        QMultiMap<double,QVector<double> >::iterator it0,it1, it2;

         for(it0=txtData.begin(); it0!=txtData.end();){
             double y0 = it0.key();
             it1 = txtData.lowerBound(y0);
             it2 = txtData.upperBound(y0);
             QVector<double> tmp;
             while(it1!=it2){
                 QVector<double> xc;
                 xc = it1.value();
                 double x = xc.at(0);
                 double c = xc.at(1);
                 tmp.push_back(x);
                 tmp.push_back(c);
                 it1++;
             }
             sortD.insert(y0,tmp);
             tmp.clear();
             it0 = it2;
         }
         txtData.clear();
         /*
         qDebug()<<"验证";
        QMap<double,QVector<double> >::iterator k;
         for(k = sortD.begin();k!=sortD.end();k++){
             qDebug()<<k.key()<<k.value();
         }
*/

         processSortD(sortD);
    }else return ;
}

void dealDatas::processSortD(QMap<double, QVector<double> >&sortD)
{
    if(!sortD.isEmpty()){
        QVector<double> available;//距离<0.07倍根号2的距离和云值
        QVector<double> realP;//距离<0.05的最近点的距离和云值


        double c =0;
        for(int k=0; k<monthData.length(); k++){//monthData.length()
            QVector<double> p5;
            QVector<double> p7;

            double x0 =monthData.at(k).x;
            double y0 =monthData.at(k).y;
           // qDebug()<<"坐标"<<x0<<y0;

            QMap<double,QVector<double> >::iterator t1,t2;
            if((y0-0.1)>(sortD.end()-1).key()){
                monthData[k].cloud.append(0);
                return ;
            } else {
                t1 = sortD.lowerBound(y0-0.1);
            }

            if((y0+0.1)<sortD.begin().key()){
                monthData[k].cloud.append(0);
                return ;
            }

            else{
                if((y0+0.1)>(sortD.end()-1).key()){
                    t2 = sortD.end()-1;
                }else t2 =sortD.upperBound(y0+0.1);

            }

            while(t1!=t2){
               double y = t1.key();
               double x =0,c=0;
               QVector<double> v1;
               v1 = t1.value();
              // qDebug()<<"v1的长度"<<v1.size();
               for(int i=0; i<(v1.length()/2); i++){
                   x = v1.at(2*i);
                   c = v1.at(2*i+1);
                   double dis = sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0));


                   if(dis<0.05){
                       available.append(dis);
                       available.append(c);
                       realP.append(dis);
                       realP.append(c);
                       p5.append(x);
                       p5.append(y);
                       p5.append(c);
                   }
                   else if(dis<0.07*sqrt(2)){
                       available.append(dis);
                       available.append(c);
                       p7.append(x);
                       p7.append(y);
                       p7.append(c);

               }
               else{}

            }
               t1++;
        }

            //求每个点对应的云值
            c = findC(available,realP);
           monthData[k].cloud.append(c);

         /*  qDebug()<<"坐标"<<x0<<y0<<"yun"<<c;
           for(int nu=0;nu<(p5.length()/3);nu++){
               qDebug()<<"小于0.05"<<p5.at(nu*3)<<p5.at(nu*3+1)<<p5.at(nu*3+2);
           }
           for(int nu=0;nu<(p7.length()/3);nu++){
               qDebug()<<"小于0.07"<<p7.at(nu*3)<<p7.at(nu*3+1)<<p7.at(nu*3+2);
           }*/

    }
        sortD.clear();/////////////////

    }
    else return;

}

double dealDatas::findC(QVector<double> &available,QVector<double> &realP)
{
   // qDebug()<<"小于0.05"<<realP.length()/2<<"小于0.07"<<available.length()/2;

    double sum=0;
    double  s1=0,s2=0,s3=0,s4=0;
    double c1=0,c2=0,c3=0,c4=0,cloud=0;
    //如果有4个及以上取前四个
    if((realP.size()/2)>3){
        s1 = realP.at(0);
        s2 = realP.at(2);
        s3 = realP.at(4);
        s4 = realP.at(6);
        c1 = realP.at(1);
        c2 = realP.at(3);
        c3 = realP.at(5);
        c4 = realP.at(7);
        sum = s1+s2+s3+s4;
        cloud = (s1/sum)*c4+(s2/sum)*c3+(s3/sum)*c2+(s4/sum)*c1;
    }
    else if((realP.size()/2)==3){
        s1 = realP.at(0);
        s2 = realP.at(2);
        s3 = realP.at(4);
        c1 = realP.at(1);
        c2 = realP.at(3);
        c3 = realP.at(5);
        sum = s1+s2+s3;
        cloud = (s1/sum)*c3+(s2/sum)*c2+(s3/sum)*c1;
    }
    else if((realP.size()/2)==2){
        s1 = realP.at(0);
        s2 = realP.at(2);
        c1 = realP.at(1);
        c2 = realP.at(3);
        sum = s1+s2;
        cloud = (s1/sum)*c2+(s2/sum)*c1;
    }
    else if((realP.size()/2)==1){
         s1 = realP.at(0);
         c1 = realP.at(1);
         if(s1<0.002) cloud = c1;
         else cloud = refind(available);
    }
    else
        cloud  = refind(available);
   // qDebug()<<cloud;
    realP.clear();
    return cloud;
}

double dealDatas::refind(QVector<double> &avail)
{
    double sum=0;
    double  s1=0,s2=0,s3=0,s4=0;
    double c1=0,c2=0,c3=0,c4=0,cloud=0;
    //如果有4个及以上取前四个
    if((avail.size()/2)>3){
        s1 = avail.at(0);
        s2 = avail.at(2);
        s3 = avail.at(4);
        s4 = avail.at(6);
        c1 = avail.at(1);
        c2 = avail.at(3);
        c3 = avail.at(5);
        c4 = avail.at(7);
        sum = s1+s2+s3+s4;
        cloud = (s1/sum)*c4+(s2/sum)*c3+(s3/sum)*c2+(s4/sum)*c1;
    }
    else if((avail.size()/2)==3){
        s1 = avail.at(0);
        s2 = avail.at(2);
        s3 = avail.at(4);
        c1 = avail.at(1);
        c2 = avail.at(3);
        c3 = avail.at(5);
        sum = s1+s2+s3;
        cloud = (s1/sum)*c3+(s2/sum)*c2+(s3/sum)*c1;
    }
    else if((avail.size()/2)==2){
        s1 = avail.at(0);
        s2 = avail.at(2);
        c1 = avail.at(1);
        c2 = avail.at(3);
        sum = s1+s2;
        cloud = (s1/sum)*c2+(s2/sum)*c1;
    }
    else if((avail.size()/2)==1){
         s1 = avail.at(0);
         c1 = avail.at(1);
         if(s1<0.002) cloud = c1;
         else cloud = 0;
    }
    else
        cloud  =0;
   // qDebug()<<cloud;
    avail.clear();
    return cloud;
}

void dealDatas::calculateSave(QString str)
{
     qDebug()<<"计算和保存";
     QString str0 = "E:/FirstYGraduate/result/";
    // QString str = QString("%1").arg(i);
     QString name = str0 + str+".csv";
     QFile file(name);
     QTextStream out(&file);
     file.open(QIODevice::WriteOnly | QIODevice::Text);
     out<<"XCoord"<<","<<"YCoord"<<","<<"Num"<<","<<"Total"<<","<<"Cloud"<<"\n";
     for(int i=0;i<monthData.length();i++){
         double x = monthData.at(i).x;
         double y = monthData.at(i).y;
         int cnt = monthData[i].cloud.length();
         int n = 0;
         double average = 0;
         double total = 0;
         for(int k=0;k<cnt;k++){
             if(monthData[i].cloud.at(k)!=0){
                 total+=monthData[i].cloud.at(k);
                 n++;
             }

             else{
                 //cnt-=1;
             }
          }
         average = total/n;
          out <<x<<","<<y<<","<<n<<","<<total<<","<<average<<"\n";

         //saveFile(x,y,cnt,total,average);
     }
     monthData.clear();
}

void dealDatas::run()
{
    qDebug()<<"子线程id"<<QThread::currentThreadId();
    readData();
}


