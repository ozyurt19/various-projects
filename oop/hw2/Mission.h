#ifndef MISSION_H
#define MISSION_H 
#include "Person.h" 

class Mission{
    string name;
    int missionNumber;
    int cost;
    int faultProbability;
    bool completed;
    Passenger * passengers;
    Astronaut * crew;
    static int numMissions;
    int passenger_num;
    int crew_num;
    public:
    Mission(string, int, int);
    Mission();
    ~Mission();
    Mission operator+=(Passenger *); 
    Mission operator+=(Astronaut *); 
    bool executeMission();
    int calculateProfit(int);
    string getName(){return name;};
    void setName(string name_in){name = name_in;};
    int get_mission_number(){return missionNumber;};
    int get_cost(){return cost;};
};

#endif /* MISSION_H */