#include <iostream>
#include <string>
#include <vector>
#include "Tickets.h"

Tickets::Tickets(): row(0), seat(0), bought(false), booked(false) {}

void Tickets::p()
{
    std::cout<<"    -> Row: "<<row<<" Seat: "<<seat<<" / ";
    if(bought)
    std::cout<<"Bought\n";
    else if(booked)
    std::cout<<"Booked\n";
}

void Tickets::pBook()
{
    if(booked)
    std::cout<<"    -> Row: "<<row<<" Seat: "<<seat<<" Booked\n";
}

void Tickets::createcode(std::string hall,std::string data,std::string name)
{
    code+="R";
    int row2=0;

    for(int r=row;r;r/=10)
    row2=row2*10+r%10;

    for(;row2;row2/=10)
        code+=char(row2%10+'0');


    code+="_S";
    int seat2=0;
    for(int s=seat;s;s/=10)
    seat2=seat2*10+s%10;

    for(;seat2;seat2/=10)
        code+=char(seat2%10+'0');
    
    std::string znak="#$^|/~()";
    code+=znak[(row+seat)%8];
    std::string abc16="AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz",s=name+data;
    int num=0;
    for(int i=0;i<s.size();i++)
    {
        num+=s[i];
    }
    for(;num;num/=8)
        code+=abc16[num%52];
    
    code+=znak[(row+seat)%8];
    code+=hall;
    //std::cout<<code<<"\n";
}
