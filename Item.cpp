#include"item.h"
#include<QDebug>
void Item::set_position(const int &xx, const int &yy)
{
    x=xx;
    y=yy;
}
void Item::set_size(const int &wwidth, const int &hheight)
{
    width=wwidth;
    height=hheight;
}
void Item::set_price(const int &pprice)
{
    price=pprice;
}
void Item::set_speed(const double &sspeed)
{
    speed=sspeed;
}
void Item::set_kind(const int &kkind)
{
    kind=kkind;
}

void Item::set_visible()//设置为可见
{
    visible=true;
}

void Item::set_invisible()//设置为不可见
{
    visible=false;
}

void Item::init()//初始化
{
    x=y=height=width=kind=0;
    visible=true;
}

bool Item::detection(const int &xx,const int &yy)//item碰撞检测
{
    if(visible==true&&xx>x+5&&xx<(x+width-5)&&yy>y+2&&yy<(y+height-5))//+5、-5是为了缩小碰撞检测范围
        return true;
    return false;
}
