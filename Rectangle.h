#pragma once
#include"Shape.h"
using std::ostream;
class Rectangle:public Shape
{
protected:
    int x,y,width,height;
    std:: string filling;
public:
    Rectangle(int _x,int _y,int _width,int _height,const std:: string& _filling)
    {
        type="rectangle";
        x=_x;
        y=_y;
        width=_width;
        height=_height;
        filling=_filling;
    }
    void print()
    {
        std:: cout<<"rectangle"<<" "<<x<<" "<<y<<" "<<width<<" "<<height<<" "<<filling<<std::endl;
    }
    void printInFile(ostream& out)
    {
        out<<"  <"<<"rect "
            <<"x="<<'"'<<x<<'"'<<" "
            <<"y="<<'"'<<y<<'"'<<" "
            <<"width="<<'"'<<width<<'"'<<" "
            <<"height="<<'"'<<height<<'"'<<" "
            <<"fill="<<'"'<<filling<<'"'<<" />"<<'\n';
    }
    void translation(int _vertical,int _horizontal)
    {
        x=x+_horizontal;
        y=y+_vertical;
    }
    friend ostream& operator <<(ostream& , Rectangle&);
};
ostream& operator <<(ostream& out, Rectangle& other)
{
    other.printInFile(out);
    return out;

}


