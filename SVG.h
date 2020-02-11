#pragma once
#include"Shape.h"
#include<fstream>
#include<iostream>
const int FILEMARKER=132;
using std:: string;
using std::cout;
using std::ios;
const unsigned MAX_CAPACITY=100;
class SVG
{
private:
    string nameOfFile;
    Shape** shapes;
    unsigned capacity;
    unsigned numberOfShapes;
    void resizeT()
    {
        capacity=2*capacity;
        Shape** temp;
        temp=new Shape*[capacity];
        for(int i=0;i<numberOfShapes;i++)
        {
            temp[i]=shapes[i];
        }
        delete[] shapes;
        shapes=temp;

    }
public:
    int getNumberOfShapes()
    {
        return numberOfShapes;
    }
    SVG(string _nameOfFile)
    {

        nameOfFile=_nameOfFile;
        numberOfShapes=0;
        capacity=MAX_CAPACITY;
        shapes=new Shape*[capacity];
    }
    SVG(string _nameOfFile,Shape** _shapes,unsigned _numberOfShapes)
    {
        capacity=MAX_CAPACITY;
        nameOfFile=_nameOfFile;
        numberOfShapes=_numberOfShapes;
        shapes=new Shape*[numberOfShapes];
        for(int i=0;i<numberOfShapes;i++)
        {
            shapes[i]=_shapes[i];
        }


    }
    ~SVG()
    {
        for(int i=0;i<numberOfShapes;i++)
        {
            delete shapes[i];
        }
        delete[] shapes;
    }
    void print()
    {
        if(numberOfShapes==0)
        {
            cout<<"There are not any figures!"<<std::endl;
        }
        for(int i=0;i<numberOfShapes;i++)
        {
            cout<<i+1<<". ";
            shapes[i]->print();
        }
    }
    void translate(int _vertical,int _horizontal)
    {
        for(int i=0;i<numberOfShapes;i++)
        {
            shapes[i]->translation(_vertical,_horizontal);
        }
    }
    bool correctIndex(unsigned index)
    {
        return index<numberOfShapes;
    }
    void eraseT(unsigned index)
    {
        for(int i=index;i<=numberOfShapes/*-2*/;i++)
            shapes[i]=shapes[i+1];
        numberOfShapes--;
    }
    string getTypeOfShape(int index)
    {
        return shapes[index]->getType();
    }
    void createCircle(int _x,int _y,int _r,string _filling)
    {
        if(numberOfShapes>=capacity)
        {
            resizeT();
        }
        Shape** temp=new Shape*[numberOfShapes+1];
        for(int i=0;i<numberOfShapes;i++)
        {
            temp[i]=shapes[i];
        }
        temp[numberOfShapes]=new Circle(_x,_y,_r,_filling);
        delete[] shapes;
        shapes=temp;
        numberOfShapes++;

    }
    void createRectangle(int x,int y,int width,int height,string filling)
    {

        if(numberOfShapes>=capacity)
        {
            resizeT();
        }
        Shape** temp=new Shape*[numberOfShapes+1];
        for(int i=0;i<numberOfShapes;i++)
        {
            temp[i]=shapes[i];

        }
        temp[numberOfShapes]=new Rectangle(x,y,width,height,filling);
        delete[] shapes;
        shapes=temp;
        numberOfShapes++;
    }
    void createLine(int x1,int y1,int x2,int y2,string filling)
    {

        if(numberOfShapes>=capacity)
        {
            resizeT();
        }
        Shape** temp=new Shape*[numberOfShapes+1];
        for(int i=0;i<numberOfShapes;i++)
        {
            temp[i]=shapes[i];

        }
        temp[numberOfShapes]=new Line(x1,y1,x2,y2,filling);
        delete[] shapes;
        shapes=temp;
        numberOfShapes++;
    }
    void saveAs(char* newFile,char* oldFile)
    {
        std::ofstream out(newFile);
        std::ifstream in(oldFile);
        char p;
        in.seekg(0,ios::beg);
        int countMarker=0;
        while(countMarker<FILEMARKER)
        {
            in>>p;
            if(in.peek()==32)
            {
                out<<p<<' ';
                countMarker++;

            }
            else if(in.peek()==10)
            {
                out<<p<<'\n';
                countMarker++;

            }
            else
            {
                out<<p;
                countMarker++;}
            }
        for(int i=0;i<numberOfShapes;i++)
        {
            out<<*shapes[i];
        }
        out<<"</svg>";
        out.close();
        in.close();
    }
    void save(char* fileName)
    {
        int countMarker=0;
        char helpFile[13]="helpFile.svg";
        std:: ofstream out(helpFile);
        saveAs(helpFile,fileName);
        out.close();
        std::ifstream in(helpFile);
        std::ofstream fileToSave(fileName);
        char p;
        while(countMarker<FILEMARKER)
        {
           in>>p;
            if(in.peek()==32)
            {
                fileToSave<<p<<' ';
                countMarker++;


            }
            else if(in.peek()==10)
            {
                fileToSave<<p<<'\n';
                countMarker++;

            }
            else
            {
                fileToSave<<p;
                countMarker++;
            }

        }
        for(int i=0;i<numberOfShapes;i++)
        {
            fileToSave<<*shapes[i];
        }
        fileToSave<<"</svg>";
        fileToSave.close();
        in.close();
    }

};



