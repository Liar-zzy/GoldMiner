#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



    w.show();
    /*
     * 加速药水，矿工和钩子速度变快
     * 减速药水，。。。。变慢
     * 随机金币（100-1000）
     * 磁铁(吸收所有矿石，并且重置矿石)
     * XX(-100分)
     * 时间药水（延时）
     *
     *
     */

    return a.exec();
}
