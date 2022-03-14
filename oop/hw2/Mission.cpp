#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <time.h>
  
#include "Mission.h"  

Mission::Mission(string name_in = "AA-00", int cost_in = 0, int faultProbability_in = 0){
    cost = cost_in;
    faultProbability = faultProbability_in;
    if(isupper(name_in[0]) && isupper(name_in[1]) && name_in.substr(2, 1) == "-" && isdigit(name_in[3]) && isdigit(name_in[4]) && name_in.size() == 5){
        name = name_in;
    }
    else{
        name = "AA-00";
        cerr << "Given name does not satisfy the mission naming convention. Please set a new name!" << endl;
    }
    passenger_num = 0;
    passengers = NULL;
    crew_num = 0;
    crew = NULL;
    numMissions++;
    missionNumber = numMissions;
}

Mission::Mission(){
    name = "AA-00";
    passenger_num = 0;
    passengers = NULL;
    crew_num = 0;
    crew = NULL;
    cost = 0;
    faultProbability = 0;
    //did not incremented numMission bc all arrays i created use this constructor and it makes missionNumber variable false for missions.
}

Mission::~Mission(){}

Mission Mission::operator+=(Passenger * in)
{
    if(in->get_ticket()){
        passenger_num++;
        if(passengers == NULL){
        passengers = in;
        return *this;
        }
        in->set_next(passengers);
        passengers = in;
        return *this;
    }
    cerr << "Passenger " << in->get_name() << " " << in->get_surname() << " does not have a valid ticket!" << endl;
    return *this;
}

Mission Mission::operator+=(Astronaut * in)
{
    if(crew == NULL){
        crew = in;
        crew_num++;
        return *this;
    }
    in->set_next(crew);
    crew = in;
    crew_num++;
    return *this;
}

bool Mission::executeMission(){
    srand(time(0));
    int random = rand() % 100;
    if(random > faultProbability){
        cout << "MISSION " << name << " SUCCESSFUL!" << endl;
        int k = 0;
        Astronaut temp[crew_num + 1];
        while(k < crew_num){
            crew->completeMission(); 
            temp[k].set_name(crew->get_name());
            temp[k].set_surname(crew->get_surname());
            temp[k].set_num_missions(crew->get_num_missions());
            crew = crew->get_next();
            k++;
        }
        k--;
        while(k >= 0){
            cout << "Astronaut " << temp[k].get_name() << " " << temp[k].get_surname() << " successfully completed " << temp[k].get_num_missions() << " missions." << endl;
            k--;
        }
        completed = true;
        return true;
    }
    cout << "MISSION " << name << " FAILED!" << endl;
    completed = false;
    return false;    
}

int Mission::calculateProfit(int ticket_price){
    int i = 0;
    if(completed == true){
        i += (ticket_price * passenger_num);
    }
    i -= cost;
    return i;
}