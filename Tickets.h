#ifndef TICKETS_H
#define TICKETS_H
#include <bits/stdc++.h> 

class Tickets
{
    //private:
    public:
    int row,seat;
    bool bought,booked;
    std::string noteTic;
    std::string code;
    
    public:
    Tickets ();
    void setRow (int x) {row=x;};
    void setSeat (int x) {seat=x;};
    void setBought (bool x){bought=x;};
    void setBooked (bool x){booked=x;}; 
    void setNote (std::string x){noteTic=x;};    
    int getRow() const {return row;} 
    int getSeat() const {return seat;}
    bool getBooked() const {return booked;}
    bool getBought() const {return bought;}
    std::string getCode() const {return code;}
    void p();
    void createcode(std::string,std::string,std::string);
    void pBook();
    
};

#endif
