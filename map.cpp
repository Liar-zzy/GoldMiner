#include"map.h"
Map::Map()
{
    for(int i=0;i<15;i++)//初始化item数组
        item[i]=new Item;
}
QPoint Map::get_point(const int &i)
{
    QPoint p(item[i]->get_x(),item[i]->get_y());
    return p;
}
int Map::get_kind(const int &i)
{
    return item[i]->get_kind();
}

bool Map::is_visible(const int &i)
{
    return item[i]->is_visible();
}

bool Map::detection(const int &x,const int &y)
{
    for(int i=0;i<15;i++){
        if(item[i]->detection(x,y))//如果碰到了任意一个物体
        {
            cur_item=i;
            return true;
        }
    }
}
void Map::invisible()
{
    item[cur_item]->set_invisible();
}
void Map::rrand()
{
    srand(time(NULL));
    int times=1+rand()%3;//随机生成1-3个
    int count=0;
    while(count<times)
    {
        int i=6+rand()%4;
        if(item[i]->is_visible()==false)
        {
            item[i]->set_visible();
            int w=50+rand()%600;
            int h=120+rand()%400;
            item[i]->set_position(w,h);
            if(i==6)//如果是大矿石
            {
                item[i]->set_size(140,120);
                item[i]->set_price(500);
                item[i]->set_speed(-2);
                item[i]->set_kind(0);
            }
            else if(i==9)//是钻石
            {
                item[i]->set_size(60,50);
                item[i]->set_price(700);
                item[i]->set_speed(-3);
                item[i]->set_kind(0);
            }
            else{//如果是小矿石
                item[i]->set_size(60,50);
                item[i]->set_price(200);
                item[i]->set_speed(-4);
                item[i]->set_kind(0);
            }
            count++;
        }
        //只要不是所有随机矿石都被占满，就继续进行循环
        int flag=1;
        for(int i=6;i<10;i++)
            if(item[i]->is_visible()==false)
                flag=0;
        if(flag)
            break;
    }
    //生成随机物质
    times=rand()%3;//随机生成0-2个
    count=0;
    while(count<times)
    {
        int i=10+rand()%5;
        if(item[i]->is_visible()==false)
        {
            item[i]->set_visible();
            int w=50+rand()%600;
            int h=120+rand()%400;
            item[i]->set_position(w,h);
            item[i]->set_size(60,50);
            item[i]->set_price(0);
            item[i]->set_speed(-4);
            if(i==13)
                item[i]->set_size(100,120);
            else
                item[i]->set_size(60,50);
            if(i==13){
                item[i]->set_price(700);
            }
            else{
                item[i]->set_price(0);
            }
            item[i]->set_speed(-4);
            if(i==14)
                item[i]->set_kind(1+rand()%4);
            else
                item[i]->set_kind(i-9);
            count++;
        }
        //只要不是所有随机矿石都被占满，就继续进行循环
        int flag=1;
        for(int i=10;i<15;i++)
            if(item[i]->is_visible()==false)
                flag=0;
        if(flag)
            break;
    }

}

void Map::init()
{
    srand(time(NULL));
    for(int i=0;i<6;i++)
    {
        item[i]->init();
        int w=50+rand()%600;
        int h=120+rand()%400;
        item[i]->set_position(w,h);
        if(i<2)
        {
            item[i]->set_size(140,120);
            item[i]->set_price(500);
            item[i]->set_speed(-2);
        }
        else{
            item[i]->set_size(60,50);
            item[i]->set_price(200);
            item[i]->set_speed(-4);
        }
    }
    for(int i=6;i<15;i++)//让随机矿石不可见
    {
        item[i]->set_invisible();
    }
}
