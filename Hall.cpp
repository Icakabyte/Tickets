#include <iostream>
#include <string>
#include <vector>
#include "Hall.h"

Hall::Hall(): name(0), n(0), m(0) {}

void Hall::add_hall(std::string&str,bool&canAdd)
{
    int pos=str.find(" ");
    for(int i=0;i<pos;i++)
    {
        if(str[i]-'0'>=0&&str[i]-'0'<=9)
        name=name*10+ int(str[i]-'0');
        else
        {
            canAdd=false;
            return;
        }
    }
    str.erase(0,pos+1);
    pos=str.find(" ");
    for(int i=0;i<pos;i++)
    {
        if(str[i]-'0'>=0&&str[i]-'0'<=9)
        n=n*10+ int(str[i]-'0');
        else
        {
            canAdd=false;
            return;
        }
    }
    str.erase(0,pos+1);
    for(int i=0;i<str.size();i++)
    {
        if(str[i]-'0'>=0&&str[i]-'0'<=9)
        m=m*10+ int(str[i]-'0');
        else
        {
            canAdd=false;
            return;
        }
    }
    return;
}
