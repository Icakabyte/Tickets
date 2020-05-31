#include <bits/stdc++.h> 
#include <fstream>
#include "Event.cpp"
#include "Tickets.cpp"
#include "Hall.cpp"
#include "Function.cpp"
std::vector<Hall> hall;
std::vector<Event> events;
std::vector<Tickets> tickets;

void open()
{
    std::cout<<"Open hall's file!\n";
    Function::openHallFile(hall);
    
    bool havehall=false;
    while(!havehall)
    {
        if(hall.size()>0)
        havehall=true;
        else
        {
            std::cout<<"There are zero halls in this file!\nAdd halls or open other file.\n";
            Function::openHallFile(hall);
        }
    }
    std::cout<<"Now open Event&Tickets's file!\n";
    return;
}

int main ()
{
    open();
    
    std::string namefile;
    bool fileisopen=false;
    for(;;)
    {
        std::string str;
        std::string command;
        std::cout<<">_ ";
        std::cin>>command;
        std::getline(std::cin,str);
        str.erase (0,1);

        if(command=="open")
        {
            if(!fileisopen)
            {
                namefile=str;
                fileisopen=true;
                Function::OPEN(events,tickets,str,hall);
            }
            else
            std::cout<<"You already have opened file!\n";
        }
        
        else if(command=="addevent" && fileisopen)
            Function::addevent(events,str);
        
        else if(command=="buy" && fileisopen)
            Function::buy(events,str,hall);
        
        else if(command=="book" && fileisopen)
            Function::book(events,str,hall);
        
        else if(command=="unbook" && fileisopen)
            Function::unbook(events,str);
        
        else if(command=="bookings" && fileisopen)
            Function::bookings(events,str);
        
        else if(command=="check" && fileisopen)
            Function::check(events,str);
        
        else if(command=="freeseats" && fileisopen)
            Function::freeseats(events,hall,str);
        
        else if(command=="report" && fileisopen)
            Function::report(events,hall,str);
        
        else if(command=="save" && fileisopen)
            Function::save(events,namefile);
        
        else if(command=="saveas" && fileisopen)
            Function::saveAS(events,str);
        
        else if(command=="help" && fileisopen)
            Function::help();
        
        else if(command=="close" && fileisopen)
        {
            fileisopen = false;
            hall.clear();
            events.clear();
            tickets.clear();
            std::cout<<"Successfully closed "<<namefile<<"\n\n";
            open();//като се стартира от тук цикли за 4/5 секунди, НО РАБОТИ!!!
        }
        
        else if(command == "exit")
        break;

        else
            std::cout<<"Command not found!\n";
        
    Function::sortEvents(events);
    }
    return 0;
}
