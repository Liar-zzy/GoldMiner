#include "item_small.h"

Item_Small::Item_Small()
{
    init();
}

void Item_Small::init()
{
    x=y=height=width=0;
    price=100;
    this->set_size(60,50);
    visible=true;
    speed=-2;
}
