#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include <QMessageBox>
#include<QThreadPool>

#include "readfilepath.h"
#include "readandwrite.h"
#include "cloudamountprocessing.h"
#include "sunshinerateprocessing.h"
#include "clarityprocessing.h"
#include "radiationprocessing.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->cloudProcessing_btn,SIGNAL(clicked(bool)),this,SLOT(slotCloudProcessing_btn_clicked()));
    connect(ui->otherProcessing_btn,SIGNAL(clicked(bool)),this,SLOT(slotOtherProcessing_btn_clicked()));
//    qDebug()<<"QCoreQpplication current Path:"<<QCoreApplication::applicationDirPath();如果要取得exe运行的当前路径，就应该使用这个接口
//    qDebug()<<"Current file Path"<<dir.absolutePath();这个是从C：/来读取的路径，奇怪？？？？
    //配置文件：将数据和结果放在D盘
    ReadFilePath readPath;
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
 * 此按钮按下就进行云量处理操作：
 * 1、从readFilePath类当中读取数据；
 * 2、开多线程，从配置文件中读取一次操作的线程数目；
 * 3、加入进度条，进度条最大值设为读取一共的文件条数，读完一条更新一次
 * 4、在处理数据的过程中，把每个按钮都加灰
 * 5、最好在处理完了数据之后弹出一个选择框，"是否继续进行下部分的数据处理？",就直接进行下一步的处理
*/
void MainWindow::slotCloudProcessing_btn_clicked()
{
    //
    readAndWrite rwProcess;
    QStringList monthPathList = rwProcess.readFiles(ReadFilePath::basicCloudPath);
    //int threadNumbers = ReadFilePath::threadNum;
    ui->cloudProcessing_btn->setEnabled(false);\
    ui->otherProcessing_btn->setEnabled(false);
    //开线程的地方
    QThreadPool pool;
    pool.setMaxThreadCount(ReadFilePath::threadNum);
    qDebug()<<"按钮按下啦";
    foreach (QString monthPath, monthPathList)
    {
        qDebug()<<monthPath;
        cloudAmountProcessing* cloud = new cloudAmountProcessing(monthPath);
        pool.start(cloud);

    }
   // ui->cloudProcessing_btn->setEnabled(true);
   // ui->otherProcessing_btn->setEnabled(true);
}
/*
 * 此按钮按下就先后进行：
 * 日照处理->清晰度处理->辐射处理，
 * 可以考虑开多线程，同样设置进度条。
*/

void MainWindow::slotOtherProcessing_btn_clicked()
{
    ui->cloudProcessing_btn->setEnabled(false);
    ui->otherProcessing_btn->setEnabled(false);
}
//重载closeEvent，当窗口关闭时，弹出是否退出的的对话框，选择'是'就关闭，并杀死子进程
void MainWindow::closeEvent(QCloseEvent *ev)
{
    switch(QMessageBox::information(this,"提示！","是否要结束程序？","是","否","",1,0))
    {
    case 0:
        ev->accept();
        break;
    case 1:
        ev->ignore();
        break;
    }
}


