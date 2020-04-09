#ifndef ITEM_H
#define ITEM_H
class Item
{
private:
    int x,y;//该物体的坐标
    int height,width;
    int price;
    int kind;//0表示普通物质，1为加速，2为减速
    double speed;
    bool visible;
public:

    Item(){
        visible=true;
    }
    void set_position(const int &xx,const int &yy);//设置中心位置
    void set_size(const int &wwidth,const int &hheight);
    void set_price(const int &pprice);
    void set_speed(const double &sspeed);
    void set_kind(const int &kkind);
    void set_visible();//设置为可见
    void set_invisible();//设置为不可见

    int get_kind(){return kind;}
    int get_price(){return price;}
    int get_x(){return x;}
    int get_y(){return y;}
    double get_speed(){return speed;}

    bool is_visible(){return visible;}


    void init();

    bool detection(const int &xx,const int &yy);//碰撞检测
};

#endif // ITEM_H
