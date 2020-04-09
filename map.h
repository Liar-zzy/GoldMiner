#ifndef MAP_H
#define MAP_H
#include"item.h"
#include<stdlib.h>
#include<time.h>
#include<QtGui>
class Map
{
private:
    Item *item[15];
    int cur_item;
public:
    Map();
    int get_cur_item(){return cur_item;}//获取当前物体编号
    double get_cur_speed(){return item[cur_item]->get_speed();}//获取当前物体的速度
    int get_cur_price(){return item[cur_item]->get_price();}//获取当前物体的价值
    int get_cur_kind(){return item[cur_item]->get_kind();}
    QPoint get_point(const int &i);//获取第i个物体的坐标(QPoint)
    int get_kind(const int &i);
    bool is_visible(const int &i);//查看i物体是否可见

    bool detection(const int &x,const int &y);//碰撞检测

    void invisible();//使cur_item不可见
    void rrand();//随机生成矿石

    void init();
};
#endif // MAP_H
