#ifndef AGENCY_H
#define AGENCY_H 
#include "Mission.h" 

class Agency{
    string name;
    int cash;
    int ticket_price;
    Mission * completedMissions;
    Mission * nextMissions;
    int num_of_completed; //completedMissions length
    int num_of_next;      //nextMissions length
    int next_pos;         //nextMissions place
    public:
    Agency(string, int, int);
    ~Agency();
    void addMission(Mission);
    void executeNextMission();
    friend ostream &operator<<(ostream & out, const Agency&x); 
    int getTicketPrice(){return ticket_price;};
    void setTicketPrice(int in){ticket_price = in;};
};

#endif