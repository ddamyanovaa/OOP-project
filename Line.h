#pragma once
#include"Shape.h"
class Line:public Shape
{
private:
    int x1,y1,x2,y2;
    std:: string filling;
public:
    Line(int _x1,int _y1 ,int _x2,int _y2,const std:: string& _filling)
    {
        type="line";
        x1=_x1;
        y1=_y1;
        x2=_x2;
        y2=_y2;
        filling=_filling;
    }
    void print()
    {
        std:: cout<<"line"<<" "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<filling<<std::endl;
    }
    void printInFile(ostream& out)
    {
         out<<"  <"<<"line "<<"x="
            <<'"'<<x1<<'"'<<" "
            <<"y="<<'"'<<y1<<'"'<<" "
            <<"x="<<'"'<<x2<<'"'<<" "
            <<"y="<<'"'<<y2<<'"'<<" "
            <<"fill="<<'"'<<filling<<'"'<<" />"<<'\n';
    }
    void translation(int _vertical,int _horizontal)
    {
        x1=x1+_horizontal;
        y1=y1+_vertical;
        x2=x2+_horizontal;
        y2=y2+_vertical;

    }
    friend ostream& operator <<(ostream&, Line&);
};

ostream& operator <<(ostream& out ,Line& other)
{
    other.printInFile(out);
    return out;
}
