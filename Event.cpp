#include <iostream>
#include <string>
#include <vector>
#include "Event.h"
#include "Tickets.h"

void Event::make_event(std::string& str)
{
    size_t pos=str.find(" ");
    dataEvent=str.substr(0,pos);

    str.erase(0,pos+1);
    pos=str.find(" ");
    hallEvent=str.substr(0,pos);

    str.erase(0,pos+1);
    nameEvent=str;

    str.erase(0,str.size());
    return;
}

void Event::print()
{
    std::cout<<"\nEvent: "<<nameEvent<<"   Data: "<<dataEvent<<"   ZALA: "<<hallEvent<<"\n";
    for(int i=0;i<ticketsforevent.size();i++)
        ticketsforevent[i].p();
}

void Event::printBook()
{
    bool havebooked=false;
    for(int i=0;i<ticketsforevent.size();i++)
    {
        if(ticketsforevent[i].getBooked())
        {
            havebooked=true;
            break;
        }
    }
    if(havebooked)
    {
        std::cout<<"\nEvent: "<<nameEvent<<"   Data: "<<dataEvent<<"   ZALA: "<<hallEvent<<"\n";
        for(int i=0;i<ticketsforevent.size();i++)
            ticketsforevent[i].pBook();
    }
}

bool Event::checkcode(std::string _code)
{
    for(int i=0;i<ticketsforevent.size();i++)
    {
        if(_code==ticketsforevent[i].getCode())
        {
            std::cout<<"\nEvent: "<<nameEvent<<"   Data: "<<dataEvent<<"   ZALA: "<<hallEvent<<"\n";
            ticketsforevent[i].p();
            return true;
            break;
        }
    }
    return false;
}
