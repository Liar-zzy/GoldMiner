#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtGui>
#include<QLabel>
#include<QTimer>
#include<QKeyEvent>

#include<item.h>
#include<miner.h>
#include<map.h>
#include<QMediaPlayer>
#include <QVideoWidget>

#include <QThread>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);

    bool detection();//碰撞检测， 判断是否碰到物体
    void do_stop();
    void resume();
    void init();//初始化

    ~MainWindow();
protected:
    //void closeEvent(QCloseEvent *);
private slots:
    void timereduce();//倒计时
    void rotate();//旋转
    void ss();
    void mm();//随机生成石头的事件


    void on_toolButton_reset_clicked();

    void on_toolButton_continue_clicked();

    void on_toolButton_start_clicked();

    void on_toolButton_ppause_clicked();

    void on_toolButton_restart_clicked();

    void on_toolButton_cancel_clicked();

    void on_musicpause_clicked();

    void on_musicplay_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap pix;//绘画
    QImage background,hook;//图片

    int interval_angle;
    int time_left;
    bool AmazingCrazy=false;

    int cur_item;
    double rad;//表示1弧度=多少度
    int angle_change;
    int k;//表示倍数

    Miner *miner;
    Map *map;

    //计时器
    QTimer timer_angle,timer_clock,timer_s;
    //int interval_angle;
    int interval_miner;
    //int time_left;
    int time;//表示已经进行了多久，每10秒随机产生一次矿石
    int time_up,time_down;//表示加速和减速的持续时间

    QLabel *lable[15];//前2个为大金矿，后4个为小金矿,6-9为随机产生的石头（可重复产生）
    //Item *item[10];
    QMediaPlayer *player =new QMediaPlayer;
    QMediaPlayer *player1=new QMediaPlayer;
    QMediaPlayer *player2=new QMediaPlayer;
    QMediaPlayer *player3=new QMediaPlayer;
    QMediaPlayer *player4=new QMediaPlayer;
    QMediaPlayer *player5=new QMediaPlayer;

    QMediaPlayer *movie=new QMediaPlayer;
    QVideoWidget *videoWidget = new QVideoWidget;


};

#endif // MAINWINDOW_H
