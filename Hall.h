#ifndef HALL_H
#define HALL_H
#include <bits/stdc++.h> 

class Hall
{
    private:
    int name;
    int n,m; //rows columns

    public:
    Hall ();
    void add_hall(std::string&,bool&);
    int getName() const {return name;}
    int getN() const {return n;}
    int getM() const {return m;}
};

#endif
