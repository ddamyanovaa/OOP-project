#pragma once
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"Shape.h"
class Circle:public Shape
{
private:
    int x,y,r;
    std:: string filling;
public:
    Circle(int _x,int _y,int _r,const std::string& _filling)
    {
        type="circle";
        x=_x;
        y=_y;
        r=_r;
        filling=_filling;
    }
    void print()
    {
         std:: cout<<"circle"<<" "<<x<<" "<<y<<" "<<r<<" "<<filling<<std::endl;
    }
    void printInFile(ostream& out)
    {
         out<<"  <"<<"circle "<<"cx="
            <<'"'<<x<<'"'<<" "
            <<"cy="<<'"'<<y<<'"'<<" "
            <<"r="<<'"'<<r<<'"'<<" "
            <<"fill="<<'"'<<filling<<'"'<<" />"<<'\n';
    }
    void translation(int _vertical,int _horizontal)
    {
        x=x+_horizontal;
        y=y+_vertical;
    }
    friend ostream& operator <<(ostream&, Circle&);
};
ostream& operator <<(ostream& out ,Circle& other)
{
    other.printInFile(out);
    return out;
}
