#include<iostream>
#include"Circle.h"
#include"Line.h"
#include"Rectangle.h"
#include"Shape.h"
#include"SVG.h"
#include<fstream>
#include <sstream>
#include <cstring>
using std:: cin;
using std:: cout;
using std:: string;
using std::ifstream;
using std:: ios;
const int MIN_SHAPES=20;
const int MIN_LEN=20;
void positiveParameters(int& x,int& y,int& _x,int& _y)
{
    if(x<0)
        x=x*(-1);
    if(y<0)
        y=y*(-1);
    if(_x<0)
        _x=_x*(-1);
    if(y<0)
        _y=_y*(-1);

}
void positiveParametersForCircle(int& cx,int& cy,int& r)
{
    if(cx<0)
        cx=cx*(-1);
    if(cy<0)
        cy=cy*(-1);
    if(r<0)
        r=r*(-1);
}
int main()
{
    int index1;
    string command;
    cin>>command;
    if(command!="open")
    {
        cout<<"You did not open any file.You cant make any changes.Please enter open!"<<std::endl;
        cin>>command;
    }
    char fileName[MIN_LEN];
    cin>>fileName;
    std:: ifstream in;
    in.open(fileName);
    if(in.is_open())
    {
        cout<<"Successfully opened "<<fileName<<std::endl;
        in.seekg(FILEMARKER,ios::beg);
        char c;
        string fillOfFigure;
        Shape** shapes;
        shapes=new Shape*[MIN_SHAPES];
        int parameterNum=0;
        int parameter[4]; //Parameters of each shape.
        int counterOfShapes=0;
        string type;
        while(!in.eof())
        {
            in>>type;//type of shape;
            parameterNum=0;
            while(in.peek()!=10)
            {
                if(in.peek()>57||in.peek()<48)
                {
                    in>>c;
                    if(c=='f')
                    {
                        while(c!='"')
                            in>>c;
                            in>>fillOfFigure;
                            int sz=fillOfFigure.size();
                            fillOfFigure.resize(sz-1);
                    }

                }
                else
                {
                    int number;
                    in>>number;
                    parameter[parameterNum]=number;
                    parameterNum++;
                }

        }
        if(type=="rect")
        {
            shapes[counterOfShapes]=new Rectangle(parameter[0],parameter[1],parameter[2],parameter[3],fillOfFigure);
            counterOfShapes++;
        }
        if(type=="circle")
        {
            shapes[counterOfShapes]=new Circle(parameter[0],parameter[1],parameter[2],fillOfFigure);
            counterOfShapes++;

        }
        if(type=="line")
        {
            shapes[counterOfShapes]=new Line(parameter[0],parameter[1],parameter[2],parameter[3],fillOfFigure);
            counterOfShapes++;

        }
            in>>c;
    }
    SVG new_svg(fileName,shapes,counterOfShapes);
    in.close();
    //Here starts the main work of the program!
        while(command!="exit")
        {
            cin>>command;
            if(command=="print")
            {
              new_svg.print();
            }
            else if(command=="create")
            {
                string type;
                cin>>type;

                if(type=="rectangle")
                {
                    string filling;
                    int x,y,width,height;
                    cin>>x>>y>>width>>height>>filling;
                    positiveParameters(x,y,width,height);
                    new_svg.createRectangle(x,y,width,height,filling);
                }
                else if(type=="line")
                {
                    int x1,y1,x2,y2;
                    string filling;
                    cin>>x1>>y1>>x2>>y2>>filling;
                    positiveParameters(x1,y1,x2,y2);
                    new_svg.createLine(x1,y1,x2,y2,filling);
                }
                else
                {
                    int x,y,r;
                    string filling;
                    cin>>x>>y>>r>>filling;
                    positiveParametersForCircle(x,y,r);
                    new_svg.createCircle(x,y,r,filling);
                }
                cout<<"Successfully created "<<type<<" ("<<new_svg.getNumberOfShapes()<<")"<<std::endl;

            }
            else if(command=="erase")
            {
                int index;
                cin>>index;
                if(!(new_svg.correctIndex(index-1)))
                {
                    cout<<"There is no figure number" <<" "<<index<<"!"<<std::endl;
                }
                else
                {
                    string type=new_svg.getTypeOfShape(index-1);
                    new_svg.eraseT(index-1);
                    cout<<"Erased a "<<type<<" ("<<index<<")"<<std::endl;
                }
            }
            else if(command=="translate")
            {

                int _ver,_hor;
                string vertical,horizontal;
                cin>>vertical>>_ver>>horizontal>>_hor;
                new_svg.translate(_ver,_hor);
                cout<<"Translated all figures!"<<std::endl;


            }
            else if(command=="saveas")
            {
                string pathToSave;
                cin>>pathToSave;
                char newFileName[MIN_LEN];
                cin>>newFileName;
                new_svg.saveAs(newFileName,fileName);
                cout<<"Successfully saved another "<<newFileName<<std::endl;


            }
            else if(command=="save")
            {

                new_svg.save(fileName);
                cout<<"Successfully saved the changes to "<<fileName<<std::endl;

            }


            else
            {
                if(command!="exit")
                cout<<"Invalid command.Please input a valid one!"<<std::endl;
            }
        }

        cout<<"Exiting the program..."<<std::endl;
        cout<<"Successfully exit!"<<std::endl;

        delete[] shapes;
    }
    else
    {
        cout<<"You created new empty file!"<<std::endl;
        std::ofstream newFile(fileName);
        newFile.close();

    }
return 0;
}
