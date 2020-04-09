#include"miner.h"

//关于各项数值的更改
void Miner::change_angle(const int &aangle)
{
    angle+=aangle;
}
void Miner::change_length(const double &llength)
{
    length+=llength;
}
void Miner::change_rlength(const double &rrlength)
{
    rlength+=rrlength;
}
void Miner::change_sum(const double &ssum)
{
    sum+=ssum;
}
//关于各项数值的设置
void Miner::set_speed(const double &sspeed)
{
    speed=sspeed;
}
void Miner::set_length(const double &llength)
{
    length=llength;
}
void Miner::set_rlength(const double &rrlength)
{
    rlength=rrlength;
}

//关于各布尔值的设置
void Miner::set_is_rotating(bool c)
{
    is_rotating=c;
}
void Miner::set_is_grab(bool c)
{
    is_grab=c;
}
void Miner::set_stopped(bool c)
{
    stopped=c;
}

//初始化
void  Miner::init()
{
    angle=0;//起始旋转角度为0
    speed=4;//钩子初始速度为2
    length=0;
    rlength=0;
    sum=0;

    is_rotating=true;//判断是否正在进行旋转
    is_grab=false;//当前没有抓取任何物体
    stopped=false;
    fflag=true;
}
