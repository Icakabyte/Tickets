#ifndef FUNCTION_H
#define FUNCTION_H
#include <bits/stdc++.h> 
#include "Hall.h"
#include "Event.h"
#include "Tickets.h"

class Function
{
    public:
    static void openHallFile(std::vector<Hall>&);
    static void sort_hall(std::vector<Hall>&);
    static void help();
    
    static void OPEN(std::vector<Event>&,std::vector<Tickets>&,std::string&,std::vector<Hall>&);
    static void addevent(std::vector<Event>&,std::string&);
    static void buy(std::vector<Event>&,std::string&,std::vector<Hall>&);
    static void book(std::vector<Event>&,std::string&,std::vector<Hall>&);
    static void unbook(std::vector<Event>&,std::string&);
    static void freeseats(std::vector<Event>&,std::vector<Hall>&,std::string&);
    static void report(std::vector<Event>&,std::vector<Hall>&,std::string&);
    static void bookings(std::vector<Event>&,std::string&);
    static void check(std::vector<Event>&,std::string&);
    static bool canAddEvent(Event&,std::vector<Event>&);
    static void sortEvents(std::vector<Event>&);

    
    static void save(std::vector<Event>&,std::string&);
    static void saveAS(std::vector<Event>&,std::string&);
};


#endif
