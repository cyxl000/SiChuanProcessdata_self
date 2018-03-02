#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*这个类就是一开始主界面的ui类，只提供两个按钮。
 * 云量按钮按下，就开始处理云量的数据；
 * 另一个按钮按下，就开始对日照、清晰度和辐射的数据处理。
 */
#include <QMainWindow>
#include <QCloseEvent>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *ev);
private:
    Ui::MainWindow *ui;
public slots:
    void slotCloudProcessing_btn_clicked();
    void slotOtherProcessing_btn_clicked();
};

#endif // MAINWINDOW_H
