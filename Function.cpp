#include <iostream>
#include <string>
#include <vector>
#include "Function.h"
#include "Hall.h"
#include "Tickets.h"

void Function::sort_hall(std::vector<Hall>&hall)
{
    if(hall.size()<1)
        return;
    for(int i=0;i<hall.size()-1;i++)
    {
        for(int j=i+1;j<hall.size();j++)
        {
            if(hall[i].getName()>hall[j].getName())
            std::swap(hall[i],hall[j]);
        }
    }
}

void Function::openHallFile(std::vector<Hall>&hall)
{
    bool fileisopen=false;
    std::string namefile;
    for(;!fileisopen;)
    {
        std::string command;
        std::cout<<">_ ";
        std::cin>>command;
        std::getline(std::cin,namefile);
        namefile.erase (0,1);
        if(command=="open")
        {
            fileisopen=true;
            std::fstream file (namefile);
            if (file.is_open())
            {
                std::string str;
                while ( getline (file,str) )
                {                  
                    Hall _hall;
                    bool canAddHall=true;
                    _hall.add_hall(str,canAddHall);
                    if(canAddHall)
                    hall.push_back(_hall);
                }
                file.close();
                sort_hall(hall);
            }
            else
                std::ofstream createFile(namefile);
            file.close();
        }
        else 
        {
            std::cout<<"You need to open file first!\n";
        }
    }
    std::cout<<"Do you want to add some hall?\n";
    for(;;)
    {
        std::string in;
        std::cout<<">_ ";
        std::cin>>in;
        if(in=="yes")
        {
            bool firstenter=true;
            std::cout<<"You will input halls info, until you write 'break'.\n\nFormat-> '#' 'rows' 'seats in a row'\n\n";
            for(;;)
            {
                Hall _hall;
                bool canAddHall=true;
                std::string hall_info;
                if(!firstenter)
                std::cout<<">_ ";
                std::getline(std::cin,hall_info);
                if(hall_info=="break")
                {                    
                    sort_hall(hall);
                    std::ofstream safefile (namefile);
                    for(int i=0;i<hall.size();i++)
                        safefile<<hall[i].getName()<<" "<<hall[i].getN()<<" "<<hall[i].getM()<<"\n";
                    safefile.close();
                    return;
                }
                _hall.add_hall(hall_info,canAddHall);
                for(int i=0;i<hall.size();i++)
                {
                    if(hall[i].getName()==_hall.getName())
                    canAddHall=false;
                }
                if(canAddHall && !firstenter)
                hall.push_back(_hall);
                if(!canAddHall)
                std::cout<<"Please enter valid information for hall!\n";
                firstenter=false;
            }
        }
        else if(in=="no")
        {
            break;
        }
        else
            std::cout<<"Input 'yes/no'\n";
    }
}

void Function::OPEN(std::vector<Event>&_events,std::vector<Tickets>&_tickets,std::string&namefile,std::vector<Hall>&hall)
{
    std::fstream file (namefile);
    if (file.is_open())
    {
        std::string str;
        Event event;
        Tickets ticket;
        bool eve=false, tic=false;
        while ( getline (file,str) )
        {
            std::string com=str.substr(0,str.find(" "));
            if(com=="EVENTS")
            {
                eve=true;
                tic=false;
                str.erase(0,str.find(" ")+1);
            }
            else if(com=="TICKETS")
            {
                eve=false;
                tic=true;
                str.erase(0,str.find(" ")+1);
            }
            if(eve)
            {
                event.make_event(str);
                if(Function::canAddEvent(event,_events))
                _events.push_back(event);
                else
                std::cout<<"You can't add event on this data!\n";
            }
            else if(tic)
            {
                buy(_events,str,hall);
            }
        }
        file.close();
    }
    else
    {
        std::ofstream createFile(namefile);
    }
    file.close();
    std::cout<<"\nSuccessfully opened "<<namefile<<"\n";
    return;
}

bool Function::canAddEvent(Event&event,std::vector<Event>&_events)
{
    for(int i=0;i<_events.size();i++)
    {
        if(_events[i].getData()==event.getData() && _events[i].getHall()==event.getHall())
        return false;
    }
    return true;
}

void Function::addevent(std::vector<Event>&events,std::string&str)
{
    Event _event;
    _event.make_event(str);
    if(Function::canAddEvent(_event,events))
    events.push_back(_event);
    else
    std::cout<<"You can't add event on this data!\n";
}

void Function::buy(std::vector<Event>&events,std::string&str,std::vector<Hall>&hall)
{
    int _row=0,_seat=0;
    size_t pos=str.find(" ");
    for(int i=0;i<pos;i++)
    _row= _row*10 + (int(str[i])-'0');
    str.erase(0,pos+1);

    pos=str.find(" ");
    for(int i=0;i<pos;i++)
    _seat= _seat*10 + (int(str[i])-'0');
    str.erase(0,pos+1);

    pos=str.find(" ");
    std::string _data=str.substr(0,pos);
    str.erase(0,pos+1);
    
    std::string _name=str;
    str.erase(0,str.size());
    bool warning=true;


        int _hall=0,n,m;

    std::string namehall;    
    for(int i=0;i<events.size();i++)
    {
        if(events[i].getData()==_data && events[i].getName()==_name)
        {
            namehall=events[i].getHall();
            break;
        }
    }
    for(int i=0;i<namehall.size();i++)
    {
        _hall = _hall*10 + (int(namehall[i])-'0');
    }
    for(int h=0;h<hall.size();h++)
    {
        if(hall[h].getName()  == _hall)
        {
            n=hall[h].getN();
            m=hall[h].getM();
            break;
        }
    }
    if(_row>n || _seat>m || _row<=0 || _seat<=0)
    {
        std::cout<<"Incorrect input!\n";
        return;
    }


    for(int i=0;i<events.size();i++)
    {
        if(_data == events[i].getData() && _name == events[i].getName())
        {
            warning=false;
            Tickets _tick;
            _tick.setRow(_row);
            _tick.setSeat(_seat);
            _tick.setBought(true);
            bool add_tic=true;
            std::vector<Tickets> tic=events[i].getTic();
            for(int j=0;j<tic.size();j++)
            {
                if(_tick.getRow()==tic[j].getRow() && _tick.getSeat()==tic[j].getSeat())
                {
                    add_tic=false;
                    break;
                }
            }
            if(add_tic)
            {
                _tick.createcode(events[i].getHall(),events[i].getData(),events[i].getName());
                events[i].vector_tickets(_tick);
            }
            else
            std::cout<<"This seat is occupied! You can't buy it!\n";
        }
    }
    if(warning)
    std::cout<<"Something is wrong in you input!\n";
}

void Function::book(std::vector<Event>&events,std::string&str,std::vector<Hall>&hall)
{
    int _row=0,_seat=0;
    size_t pos=str.find(" ");
    for(int i=0;i<pos;i++)
    _row= _row*10 + (int(str[i])-'0');
    str.erase(0,pos+1);

    pos=str.find(" ");
    for(int i=0;i<pos;i++)
    _seat= _seat*10 + (int(str[i])-'0');
    str.erase(0,pos+1);

    pos=str.find(" ");
    std::string _data=str.substr(0,pos);
    str.erase(0,pos+1);
    
    pos=str.find(" ");
    std::string _name=str.substr(0,pos);
    str.erase(0,pos+1);
    
    std::string _note=str.substr(0,pos);
    str.erase(0,str.size());
    

    int _hall=0,n,m;

    std::string namehall;    
    for(int i=0;i<events.size();i++)
    {
        if(events[i].getData()==_data && events[i].getName()==_name)
        {
            namehall=events[i].getHall();
            break;
        }
    }
    for(int i=0;i<namehall.size();i++)
    {
        _hall = _hall*10 + (int(namehall[i])-'0');
    }
    for(int h=0;h<hall.size();h++)
    {
        if(hall[h].getName()  == _hall)
        {
            n=hall[h].getN();
            m=hall[h].getM();
            break;
        }
    }
    if(_row>n || _seat>m || _row<=0 || _seat<=0)
    {
        std::cout<<"Incorrect input!\n";
        return;
    }

    bool warning=true;
    for(int i=0;i<events.size();i++)
    {
        if(_data == events[i].getData() && _name == events[i].getName())
        {
            warning=false;
            Tickets _tick;
            _tick.setRow(_row);
            _tick.setSeat(_seat);
            _tick.setBooked(true);
            _tick.setNote(_note);
            bool add_tic=true;
            std::vector<Tickets> tic=events[i].getTic();
            for(int j=0;j<tic.size();j++)
            {
                if(_tick.getRow()==tic[j].getRow() && _tick.getSeat()==tic[j].getSeat())
                {
                    add_tic=false;
                    break;
                }
            }
            if(add_tic)
            {
                _tick.createcode(events[i].getHall(),events[i].getData(),events[i].getName());
                events[i].vector_tickets(_tick);
            }
            else
            std::cout<<"This seat is occupied! You can't book it!\n";
        }
    }
    if(warning)
    std::cout<<"Something is wrong in you input!\n";
}

void Function::unbook(std::vector<Event>&events,std::string&str)
{
    int _row=0,_seat=0;
    size_t pos=str.find(" ");
    for(int i=0;i<pos;i++)
    _row= _row*10 + (int(str[i])-'0');
    str.erase(0,pos+1);

    pos=str.find(" ");
    for(int i=0;i<pos;i++)
    _seat= _seat*10 + (int(str[i])-'0');
    str.erase(0,pos+1);

    pos=str.find(" ");
    std::string _data=str.substr(0,pos);
    str.erase(0,pos+1);
    
    std::string _name=str;
    str.erase(0,str.size());
    
    bool warning=true;
    for(int i=0;i<events.size();i++)
    {
        if(_data == events[i].getData() && _name == events[i].getName())
        {
            warning=false;
            Tickets _tick;
            _tick.setRow(_row);
            _tick.setSeat(_seat);
            bool unbook_tic=false;
            int unbookpos=-1;
            std::vector<Tickets> tic=events[i].getTic();
            for(int j=0;j<tic.size();j++)
            {
                if(_tick.getRow()==tic[j].getRow() && _tick.getSeat()==tic[j].getSeat())
                {
                    unbook_tic=true;
                    unbookpos=j;
                    break;
                }
            }
            if(unbook_tic)
                events[i].unbookpos(unbookpos);
            else
            std::cout<<"We can't find the place you're looking for to unbooked it!\n";
        }
    }
    if(warning)
    std::cout<<"Something is wrong in you input!\n";
}

void Function::bookings(std::vector<Event>&events,std::string&str)
{
    int pos=str.find(" ");
    std::string s;
    std::string _data,_name;
    if(str[0]>='0'&&str[0]<='9')
    {
        if(pos==-1)
        _data=str;
        else
        {
            _data=str.substr(0,pos);
            str.erase(0,pos+1);
            _name=str;
        }
    }
    else
        _name=str;
    for(int i=0;i<events.size();i++)
    {
        if((events[i].getData()==_data || _data.empty()) && (events[i].getName()==_name || _name.empty()))
        {
            //std::cout<<"Data:"<<_data<<"|   name"<<_name<<"|\n";
            events[i].printBook();
        }
    }
}

void Function::check(std::vector<Event>&events,std::string&str)
{
    bool correct_code=false;
    for(int i=0;i<events.size();i++)
    {
        if(events[i].checkcode(str))
        {
            correct_code=true;
            break;
        }
    }
    if(!correct_code)
    {
        std::cout<<"\n";
        std::cout<<"         Incorrect code!\n\n";
        std::cout<<"***********************************\n";
        std::cout<<"**** Security is on its way!!! ****\n";
        std::cout<<"****      Do not move!         ****\n";
        std::cout<<"***********************************\n\n";
    }
}

void Function::freeseats(std::vector<Event>&events,std::vector<Hall>&hall,std::string&str)
{
    std::string _data,_name;
    int pos = str.find(" ");
    _data=str.substr(0,pos);
    str.erase(0,pos+1);
    _name=str;

    for(int i=0;i<events.size();i++)
    {
        if(events[i].getData()==_data && events[i].getName()==_name)
        {
            int n;
            int m,_hall=0;
            std::string namehall=events[i].getHall();
            for(int convert=0;convert<namehall.size();convert++)
            {
                _hall = _hall*10 + (int(namehall[convert])-'0');
            }
            for(int h=0;h<hall.size();h++)
            {
                if(hall[h].getName()  == _hall)
                {
                    n=hall[h].getN();
                    m=hall[h].getM();
                    break;
                }
            }
            std::cout<<"\n\n";
            std::vector<Tickets> tic=events[i].getTic();
            for(int r=0;r<n;r++)
            {
                std::cout<<"    ";
                for(int s=0;s<m;s++)
                {
                    bool free=true;
                    for(int t=0;t<tic.size();t++)
                    {
                        if(tic[t].getRow()==r+1 && tic[t].getSeat()==s+1)
                        {
                            free=false;
                            break;
                        }
                    }
                    if(free)
                    std::cout<<"O ";
                    else
                    std::cout<<"  ";
                }
                std::cout<<"\n";
            }
            std::cout<<"\nReserved or sold:\n";
            for(int t=0;t<tic.size();t++)
                tic[t].p();
            std::cout<<"\n";
            break;
        }
    }
}

void Function::report(std::vector<Event>&events,std::vector<Hall>&hall,std::string&str)
{
    std::string from,to,hallname;
    int pos=str.find(" ");
    from=str.substr(0,pos);
    str.erase(0,pos+1);
    pos=str.find(" ");
    bool haveHall=true;
    if(pos==-1)
    {
        haveHall=false;
        to=str;
    }
    else
    {
        to=str.substr(0,pos);
        str.erase(0,pos+1);
        hallname=str;
    }
    for(int i=0;i<events.size();i++)
    {
        if((events[i].getHall()==hallname || !haveHall) && from<=events[i].getData() && to>=events[i].getData())
        {
            std::cout<<"\nName: "<<events[i].getName()<<" Data:"<<events[i].getData()<<"\n";
            std::cout<<"Reserved or sold:";
            int sold=0;
            std::vector<Tickets> tic=events[i].getTic();
            for(int j=0;j<tic.size();j++)
            {
                if(tic[j].getBought())
                sold++;
            }
            std::cout<<"\n  Sold: "<<sold<<" tickets\n  "<<"Reserved: "<<tic.size()-sold<<" tickets\n\n";
        }
    }
}

void Function::sortEvents(std::vector<Event>&events)
{
    for(int i=0;i<events.size()-1;i++)
    {
        for(int j=i+1;j<events.size();j++)
        {
            if(events[i].getData() > events[j].getData())
            {
                std::swap(events[i],events[j]);
            }
        }
    }
}

void Function::save(std::vector<Event>&events,std::string&namefile)
{
    std::ofstream safefile (namefile);
    for(int i=0;i<events.size();i++)
    {
        safefile<<"EVENTS "<<events[i].getData()<<" "<<events[i].getHall()<<" "<<events[i].getName()<<"\n";
    }
    for(int i=0;i<events.size();i++)
    {
        std::vector<Tickets> tic=events[i].getTic();
        for(int j=0;j<tic.size();j++)
        {
            if(tic[j].getBought())
            safefile<<"TICKETS "<<tic[j].getRow()<<" "<<tic[j].getSeat()<<" "<<events[i].getData()<<" "<<events[i].getName()<<"\n";
        }
    }
    return;
}

void Function::saveAS(std::vector<Event>&events,std::string&namefile)
{    
    save(events,namefile); 
    std::cout<<"Successfully saved another "<<namefile<<"!\n";
    return;
}

void Function::help()
{
    std::cout<<"\nThe following commands are supported:\nopen <file>	opens <file>\nclose			closes currently opened file\nsave			saves the currently open file\nsaveas <file>	saves the currently open file in <file>\nhelp			prints this information\nexit			exists the program\n\n";
    return;
}
