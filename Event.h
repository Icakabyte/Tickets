#ifndef EVENT_H
#define EVENT_H
#include <bits/stdc++.h> 
#include "Tickets.h"

class Event
{
    private:
    std::string dataEvent;
    std::string hallEvent;
    std::string nameEvent;

    std::vector<Tickets> ticketsforevent;

    public:
    void make_event(std::string&);
    std::string getName() const {return nameEvent;}
    std::string getHall() const {return hallEvent;}
    std::string getData() const {return dataEvent;}
    std::vector<Tickets> getTic() const {return ticketsforevent;}
    void vector_tickets(Tickets t) {ticketsforevent.push_back(t);};
    void unbookpos(int pos) {ticketsforevent.erase(ticketsforevent.begin()+pos);};
    void print();
    void printBook();
    bool checkcode(std::string);
};

#endif
