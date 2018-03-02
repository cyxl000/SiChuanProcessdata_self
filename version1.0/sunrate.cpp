#include"sunrate.h"
#include<QMap>

CalculateRate::CalculateRate(QMultiMap<double, sunRate> sunrate,QVector<monthCloud> readCloud)
{
    this->stdcloud = sunrate;
    this->readCloud = readCloud;
    qDebug()<<"打印"<<this->readCloud.size()<<this->stdcloud.size();
    /* QMultiMap<double, sunRate>::iterator it;
    for(it = stdcloud.begin(); it!=stdcloud.end(); it++){
        sunRate s1 = it.value();
        qDebug()<<s1.x<<it.key()<<s1.a<<s1.b<<s1.idName;
    }
   for(int i = 0;i<readCloud.length();i++){
        qDebug()<<"jianyan  "<<readCloud.at(i).x<<readCloud.at(i).y<<readCloud.at(i).c;
    }
*/
}

void CalculateRate::findLearst()
{
    qDebug()<<"findLearst()";
    QMultiMap<double, sunRate>::iterator it1, it2;

    for(int i=0; i<readCloud.length(); i++){//readCloud.length()
        QMap<double,QVector<double> > Dis;
        double x0 = readCloud.at(i).x;
        double y0 = readCloud.at(i).y;
        double c = readCloud.at(i).c;
        it1 = stdcloud.lowerBound(y0-2.5);
       // qDebug()<<"ai"<<x0<<y0<<c;

       if((y0+2.5)>((stdcloud.end()-1).key())){
            it2 = stdcloud.end()-1;
        }
        else it2 = stdcloud.upperBound(y0+2.5);
        while(it1!=it2)
        {
            QVector<double> tmp;
            double y = it1.key();
            sunRate s = it1.value();
            double x = s.x;
            double a = s.a;
            double b = s.b;
            double idName = s.idName.toDouble();
            double dis = sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0));
            tmp.append(a);
            tmp.append(b);
            tmp.append(idName);
           Dis.insert(dis,tmp);
           it1++;
           tmp.clear();
        }
        /*
        qDebug()<<Dis.size();
        QMap<double,QVector<double> >::iterator point;
        point= Dis.begin();
        qDebug()<< point.key()<<point.value();
*/
        QMap<double,QVector<double> >::iterator point = Dis.begin();
        //qDebug()<<"Dis.size()"<<Dis.size();
        double s1 = point.key();
        double n1 = point.value().at(2);
        double rate1 = point.value().at(0)*c+point.value().at(1);
        point+=1;
        double s2 = point.key();
        double n2 = point.value().at(2);
        double rate2 = point.value().at(0)*c+point.value().at(1);
        point +=1;
        double s3 = point.key();
        double n3 = point.value().at(2);
        double rate3 = point.value().at(0)*c+point.value().at(1);
        point +=1;
        double s4 = point.key();
        double n4 = point.value().at(2);
        double rate4 = point.value().at(0)*c+point.value().at(1);

       // QString name = n1+" "+n2+" "+n3+" "+n4;
       // readCloud[i].idName = QString::number(name);
        double sumDis = s1+s2+s3+s4;
       // qDebug()<<"s1,s2,s3,s4"<<s1<<s2<<s3<<s4;
       // qDebug()<<"rate1,rate2,rate3,rate4"<<rate1<<rate2<<rate3<<rate4;
        double rate = rate4*s1/sumDis+rate3*s2/sumDis+rate2*s3/sumDis+rate1*s4/sumDis;
        readCloud[i].rate =rate;
       // qDebug()<<point.key()<<point.value().at(2);

        Dis.clear();
    }
    qDebug()<<"结束";

}


void CalculateRate::saveFile(QString filename)
{
    qDebug()<<"saveFile(int i)";
    QDir temp;
        bool exist = temp.exists("E://SiChuan//Result//finalRate");
        if(exist)
            qDebug()<<"文件夹已经存在！";
        else
        {
            bool ok = temp.mkdir("E://SiChuan//Result//finalRate");
            if( ok )
                qDebug()<<"文件夹创建成功！";
        }

    QString str0 = "E:/SiChuan/Result/finalRate/";

    QString name = str0 + filename;
    QFile file(name);
    QTextStream out(&file);
    if(file.exists()){
         }
    else{
             file.open(QIODevice::WriteOnly | QIODevice::Text);
             out<<"XCoord"<<","<<"YCoord"<<","<<"CloudAmount"<</*","<<"idName"*/","<<"Rate"<<"\n";
             for(int k=0; k<readCloud.length(); k++){
                out<<readCloud.at(k).x<<","<<readCloud.at(k).y<<","<<readCloud.at(k).c
                  <</*","<<readCloud.at(k).idName<<*/","<<readCloud.at(k).rate<<"\n";

             }
             }
              //...文件操作

              file.close();
              readCloud.clear();
}




