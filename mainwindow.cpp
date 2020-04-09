#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<QDebug>
#include<QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setFixedSize(700, 600);
    setWindowTitle(tr("黄金矿工"));

    QPixmap pixmap(":/images/iii/ccc.png");//自定义指针
    QCursor cursor= QCursor(pixmap,-1,-1);
    setCursor(cursor);

    interval_angle=15;
    interval_miner=200;

    miner=new Miner;
    map=new Map;

    QPalette pal;
    pal.setColor(QPalette::WindowText, Qt::yellow);//设置窗口前景色 为yellow

    ui->label_final->setPalette(pal);//设置颜色

    this->setStyleSheet("#MainWindow{border-image:url(:/images/iii/background.jpg);}");//设置背景图片
    pix.load("://images//iii//hook1.png");//设置钩子，60*50

    timer_angle.setInterval(interval_angle);//设置触发间隔为15ms
    connect(&timer_angle,&QTimer::timeout,this,&MainWindow::rotate);//链接
    connect(&timer_angle,&QTimer::timeout,this,&MainWindow::ss);

    timer_s.setInterval(interval_miner);//s控制矿工的运动
    connect(&timer_s,&QTimer::timeout,this,&MainWindow::mm);

    timer_clock.setInterval(1000);
    connect(&timer_clock,&QTimer::timeout,this,&MainWindow::timereduce);

    rad=180/3.1415926;//弧度
    angle_change=1;//角度转变量为1°

    lable[0]=ui->label_1;lable[1]=ui->label_2;lable[2]=ui->label_3;
    lable[3]=ui->label_4;lable[4]=ui->label_5;lable[5]=ui->label_6;
    lable[6]=ui->label_7;lable[7]=ui->label_8;lable[8]=ui->label_9;
    lable[9]=ui->label_10;//钻石
    lable[10]=ui->label_11;lable[11]=ui->label_12;lable[12]=ui->label_13;//11为加速，12减速，13加时间

    lable[13]=ui->label_14;//大钻石
    lable[14]=ui->label_15;//随机物品


    init();
    do_stop();//暂停，跳出帮助菜单
    ui->label_pause->setVisible(false);//暂停图案
    ui->toolButton_ppause->setVisible(false);

    ui->label_begin->setVisible(true);
    ui->toolButton_start->setVisible(true);
}
void MainWindow::init()
{
    player->setMedia(QUrl("qrc:/musicss/ii/sound.mp3"));
    player->setVolume(50);
    player->play();


    player1->setMedia(QUrl::fromLocalFile("C:/Users/Liar/Desktop/kuanggong_rc/music/ss.mp3"));
    player1->setVolume(100);


    player2->setMedia(QUrl("qrc:/musicss/ii/get.mp3"));
    player2->setVolume(100);

    player3->setMedia(QUrl("qrc:/musicss/ii/special.mp3"));
    player3->setVolume(100);

    player4->setMedia(QUrl("qrc:/musicss/ii/money.mp3"));
    player4->setVolume(50);

    player5->setMedia(QUrl("qrc:/musicss/ii/endless.mp3"));
    player5->setVolume(50);

    movie->setVideoOutput(videoWidget);
    movie->setMedia(QUrl("qrc:/moviess/i/ReadyPlayerOne.mp4"));
    movie->setVolume(100);
    videoWidget->setFixedWidth(1920);
    videoWidget->setWindowTitle(tr("ReadyPlayerOne"));

    ui->label_pause->setVisible(false);//暂停图案
    ui->toolButton_ppause->setVisible(false);

    ui->label_finish->setVisible(false);//结束图案
    ui->toolButton_restart->setVisible(false);
    ui->toolButton_cancel->setVisible(false);

    ui->label_final->setVisible(false);
    ui->lcdNumber_speed->setVisible(false);

    miner->init();//矿工初始化设置
    map->init();//地图初始化设置

    time_left=60;//剩余时间为60s
    time=time_up=time_down=0;
    k=1;
    for(int i=0;i<6;i++)
    {
        lable[i]->setVisible(true);
        lable[i]->move(map->get_point(i));
        if(i<2)
            lable[i]->resize(140,120);
        else
            lable[i]->resize(60,50);
    }
    for(int i=6;i<15;i++)//让随机矿石不可见
        lable[i]->setVisible(false);

    ui->toolButton->setStyleSheet("#toolButton{border-image:url(:/images/iii/1.png);}");//设置矿工

    ui->lcdNumber->display(time_left);//显示剩余时间
    ui->lcdNumber_sum->display(miner->get_sum());//显示当前分数
    timer_angle.start();//计时器启动
    timer_clock.start();
    timer_s.start();
}




void MainWindow::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.translate(350,120-20); //让图片的中心作为旋转的中心
    painter.rotate(miner->get_angle()); //顺时针旋转90度
    painter.translate(-350,-100); //使原点复原

    int length=miner->get_length();
    if(miner->isrotating()==false||miner->isstopped())
    {
        QPen pen;
        pen.setWidth(6);
        painter.setPen(pen);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.drawLine(350,95,350,95+length);
        painter.drawPixmap(320,95+length,pix);//绘图的起点
    }
    else
       painter.drawPixmap(320,95,pix);//绘图的起点
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{

    int key=e->key();
    if (!miner->isstopped()&&key == Qt::Key_Down) // 按向下方向键时
    {
        if(miner->isrotating())//如果正在旋转
        {
            //停止旋转，进行下拉操作
            miner->set_is_rotating(false);
            ss();
            player1->play();
        }
    }
    if(key == Qt::Key_Space)//暂停功能
    {
        if(miner->isstopped()&&time_left>0)
            resume();
        else{
            do_stop();
            }
    }
    if(key == Qt::Key_Up&&!miner->isgrab()){
        if(miner->get_length()>0&&miner->get_speed()>0){
        miner->set_speed(-1*(miner->get_speed()));
        }
    }
   if(key==Qt::Key_Z){
       interval_angle=6;
       time_left=100;
       player->stop();
       player1->stop();
       player2->stop();
       player3->stop();
       player5->play();
       AmazingCrazy=true;
    }
   if(key==Qt::Key_Right)
   {
       time_left=time_left-1;
   }
   if(key==Qt::Key_Left)
   {
       time_left=time_left+1;
   }
}
bool MainWindow::detection()//碰撞和越界检测
{
    //定义临时变量angle和length
    int angle=miner->get_angle();
    int length=miner->get_length();

    if(fabs(angle)>45){
        if(length>(350/(sin(fabs(angle/rad)))))
             return true;
    }
    else if(length>(500/(cos(angle/rad))))
             return true;
    if(map->detection(350-length*sin(angle/rad),95+length*cos(angle/rad)))//如果map.碰撞检测返回为真
    {
        miner->set_is_grab(true);
        return true;
    }
    return false;
}
void MainWindow::do_stop()
{
    if(AmazingCrazy){
        player5->pause();
    }
    else{
        player->pause();
    }

    if(time_left>0){
        ui->label_pause->setVisible(true);//暂停图案
        ui->toolButton_ppause->setVisible(true);
    }
    miner->set_is_rotating(!(miner->isrotating()));
    timer_clock.stop();
    timer_angle.stop();
    timer_s.stop();

    miner->set_stopped(true);
}
void MainWindow::resume()
{
    if(AmazingCrazy){
        player5->play();
    }else{
        player->play();
    }
    ui->label_pause->setVisible(false);//暂停图案
    ui->toolButton_ppause->setVisible(false);
  //  ui->toolButton_mpause->setVisible(false);
  //  ui->toolButton_mplay->setVisible(false);

    miner->set_is_rotating(!(miner->isrotating()));
    timer_clock.start();
    timer_angle.start();
    timer_s.start();
    miner->set_stopped(false);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::timereduce()//计时器
{
    if(time_left>=0)
    {
        time++;
        ui->lcdNumber->display(time_left--);
        if(time_down==0&&time_up==0)
        {
            k=1;
            timer_s.setInterval(interval_miner);
            timer_angle.setInterval(interval_angle);
           // ui->lcdNumber_speed->setVisible(false);
        }
        if(time_down)
        {
            k=1;
            --time_down;
            //ui->lcdNumber_speed->setVisible(true);
            //ui->lcdNumber_speed->display(time_down);
        }
        if(time_up)
        {
            --time_up;
            k=3;
           //ui->lcdNumber_speed->setVisible(true);
           // ui->lcdNumber_speed->display(time_up);
        }
        if(time%8==0)//每8秒，随机生成矿石一次
        {
            map->rrand();
            for(int i=6;i<15;i++)
                if(map->is_visible(i))//如果该物体可见
                {
                    lable[i]->setVisible(true);
                    lable[i]->move(map->get_point(i));

                }
        }
    }
    if(time_left<0)//剩余时间为0，则停止游戏
    {
        do_stop();
        player5->stop();
        ui->label_finish->setVisible(true);
        ui->toolButton_cancel->setVisible(true);
        ui->toolButton_restart->setVisible(true);
        ui->label_final->setVisible(true);
        QString s = QString::number(miner->get_sum(), 10);
        ui->label_final->setText(s);
        if(AmazingCrazy)// 疯狂模式
        {

            if(miner->get_sum()<=1000)
            {
                videoWidget->show();
                movie->play();
            }
        }
    }
}
void MainWindow::rotate()//控制旋转
{
    if(miner->isrotating())//旋转时
    {
        miner->change_angle(angle_change);
        int angle=miner->get_angle();
        if(angle>=90||angle<=-90)
            angle_change*=-1;
    }
    update();
}
void MainWindow::mm()//矿工动作设置
{
    if(!miner->isrotating())
    {
        if(miner->isfflag())//矿工的动作设置
            ui->toolButton->setStyleSheet("#toolButton{border-image:url(:/images/iii/2.png);}");
        else
            ui->toolButton->setStyleSheet("#toolButton{border-image:url(:/images/iii/3.png);}");
    }

}

void MainWindow::ss()//伸展操作
{
    if(!miner->isrotating())
    {


        if(miner->isgrab())//物体的移动
        {

            miner->change_rlength(k*fabs(miner->get_speed()));
            int rlength=miner->get_rlength();
            int angle=miner->get_angle();
            QPoint p=map->get_point(map->get_cur_item());//获取当前物体的坐标
            QPoint temp(rlength*sin(angle/rad),-rlength*cos(angle/rad));//temp为位移大小
            lable[map->get_cur_item()]->move((p+temp));
        }
        if(miner->isgrab()||detection())//如果已经抓到物体了或碰撞检测返回为true
        {
            if(miner->isgrab())
            {
                player2->play();//抓住物体后音效
                miner->set_speed(map->get_cur_speed());

            }
            else
            {
                miner->set_speed(-1*(miner->get_speed()));//速度相反，往反向拉
            }
        }

        miner->change_length(k*miner->get_speed());
        if(miner->get_length()<=0)//如果钩子回到了起点
        {
            if(miner->isgrab())//如果抓到了东西
            {
                player4->play();
                map->invisible();//令当前物体不可见
                lable[map->get_cur_item()]->setVisible(false);//令当前物体不可见
                miner->change_sum(map->get_cur_price());
                miner->set_rlength(0);
                miner->set_is_grab(false);
                if(map->get_cur_kind())//如果抓到了特殊物品
                {
                    player3->play();
                    int kind=map->get_cur_kind();
                    if(kind==1)
                    {
                        time_up=10;
                        time_down=0;//不能叠加，所以把另一个的时间归零
                        timer_s.setInterval(30);
                        k=3;
                    }else if(kind==2)
                    {
                        time_down=10;
                        time_up=0;//不能叠加，所以把另一个的时间归零
                        timer_s.setInterval(interval_miner*2);
                        timer_angle.setInterval(interval_angle*2);
                        k=1;
                    }
                    else if(kind==3){
                        time_left+=15;
                    }
                    else {
                        time_up+=10;
                        time_down=0;//不能叠加，所以把另一个时间归零
                        timer_s.setInterval(30);
                        k=3;
                        miner->change_sum(map->get_cur_price());
                    }
                }
            }
            miner->set_is_rotating(true);
            miner->set_speed(4);
        }
    }
    ui->lcdNumber_sum->display(miner->get_sum());
    update();
}
void MainWindow::on_toolButton_reset_clicked()
{
    init();
}

void MainWindow::on_toolButton_continue_clicked()
{
    if(miner->isstopped()&&time_left>0)
        resume();
    else
        do_stop();
}

void MainWindow::on_toolButton_start_clicked()
{
    ui->label_begin->setVisible(false);
    ui->toolButton_start->setVisible(false);
    resume();
}

void MainWindow::on_toolButton_ppause_clicked()
{
    resume();
}

void MainWindow::on_toolButton_restart_clicked()
{
    init();
}

void MainWindow::on_toolButton_cancel_clicked()
{
    qApp->quit();
    ui->label_finish->setVisible(false);
    ui->toolButton_cancel->setVisible(false);
    ui->toolButton_restart->setVisible(false);
}
