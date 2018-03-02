#include <QApplication>
#include"openread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenRead w;
    w.show();


    return a.exec();
}
