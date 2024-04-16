#include "mainwindow.h"

#include <QApplication>

//总操作步数 初始化
long long int MainWindow::totalSteps = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //此出处开始
    w.setFixedSize(1000,618);//设置窗口固定大小
    w.setWindowTitle("数字华容道");

    //
    w.show();

    return a.exec();
}
