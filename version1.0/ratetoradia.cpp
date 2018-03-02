#include "ratetoradia.h"
#include<QVector>
#include<QFile>
#include<QTextStream>

RateToRadia::RateToRadia(QMap<QString, State> state, QMultiMap<QString, stateAdCoeffi> locateCoffi)
{
    this->state = state;//站名和坐标
    this->locateCoffi = locateCoffi;//站名和系数
   // qDebug()<<"进入"<<this->locateCoffi.size();
}

void RateToRadia::dealDate(QVector<MonthResult> &monthresult,int cnt)
{
    this->result = monthresult;
   // qDebug()<<result.size();
    for(int i=0; i<result.length();i++){//result.length()
        double x0 = result.at(i).x;
        double y0 = result.at(i).y;
        double rate = result.at(i).coefficient;
        QMap<double,QString> Dis;
        QMap<QString, State>::iterator it;
        for(it=state.begin(); it!=state.end();it++){
            double x = it.value().x;
            double y = it.value().y;
            QString name = it.key();
            double dis = sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0));
            Dis.insert(dis,name);
        }
        QString idname1 = Dis.begin().value();
        double l1 = Dis.begin().key();
        QString idname2 = (Dis.begin()+1).value();
        double l2 = (Dis.begin()+1).key();
        QString idname3 = (Dis.begin()+2).value();
        double l3 = (Dis.begin()+2).key();
        QString idname4 = (Dis.begin()+3).value();
        double l4 = (Dis.begin()+3).key();

        QMultiMap<QString,stateAdCoeffi>::iterator nt;
        nt = locateCoffi.upperBound(idname1)-1-cnt;
       stateAdCoeffi s2 = nt.value();

       double a1 = s2.a;
       double b1 = s2.b;
       double raida1 = a1*rate+b1;

       nt = locateCoffi.upperBound(idname2)-1-cnt;
      s2 = nt.value();
      double a2 = s2.a;
      double b2 = s2.b;
      double raida2 = a2*rate+b2;

      nt = locateCoffi.upperBound(idname3)-1-cnt;
     s2 = nt.value();
     double a3 = s2.a;
     double b3 = s2.b;
     double raida3 = a3*rate+b3;

     nt = locateCoffi.upperBound(idname4)-1-cnt;
    s2 = nt.value();
    double a4 = s2.a;
    double b4 = s2.b;
    double raida4 = a4*rate+b4;

    double sum = l1+l2+l3+l4;
    double raida = (l1/sum)*raida4+(l2/sum)*raida3+(l3/sum)*raida2+(l4/sum)*raida1;
       //qDebug()<<"idname"<<idname<<"a b"<<a<<b<<raida;
       result[i].radiation = raida;
       result[i].idName = idname1+" "+idname2+" "+idname3+" "+idname4;
    Dis.clear();
    }
}

void RateToRadia::saveFile(int i)
{
    qDebug()<<"saveFile(int i)";
    QString str0 = "E:/FirstYGraduate/meteorology/GISCloudInfo/RateTo/result/";
       QString str = QString("%1").arg(i);
       QString name = str0 + str+".csv";
         QFile file(name);
         QTextStream out(&file);
         if(file.exists()){
         }else{
             file.open(QIODevice::WriteOnly | QIODevice::Text);
             out<<"XCoord"<<","<<"YCoord"<<","<<"idName"<<","<<"Radiation"<<"\n";
             for(int k=0; k<result.length(); k++){
                 out<<result.at(k).x<<","<<result.at(k).y<<","<<result.at(k).idName
                   <<","<<(result.at(k).radiation)/100<<"\n";

                }
             }
              //...文件操作

              file.close();
             qDebug()<<"结束";
    result.clear();
}
