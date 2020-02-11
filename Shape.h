#pragma once
using std::string;
using std::ostream;
class Shape
{
protected:
    string type;
public:

    virtual void print()=0;
    virtual void printInFile(ostream&)=0;
    virtual void translation(int,int)=0;
    string getType()
    {
        return type;
    }
    friend ostream& operator <<(ostream& out,Shape&);
};
ostream& operator <<(ostream& out,Shape& other)
{
   other.printInFile(out);
   return out;
}



