#include <string>
#include <iostream>
#include <cstdlib>

#include "Agency.h"   

Agency::Agency(string name_in = "default_agency_name", int cash_in = 0, int ticket_price_in = 0):name(name_in),cash(cash_in){
    if(ticket_price_in < 0){
        cerr << "Ticket price can't be negative. It is set to 0." << endl;
        ticket_price_in = 0;
    } 
    ticket_price = ticket_price_in;
    completedMissions = NULL;
    nextMissions = NULL;
    num_of_completed = 0;
    num_of_next = 0;
    next_pos = 0;
}

Agency::~Agency(){
    //delete[] completedMissions;  //it gives double free error so i did not implemented it
    //delete[] nextMissions;
}

void Agency::addMission(Mission in){
    if(num_of_next == 0){
        nextMissions = new Mission;
        nextMissions[0] = in;
        num_of_next++;
        return;
    }
    Mission temp[num_of_next];
    int k = next_pos;
    while(k < num_of_next){
        temp[k] = nextMissions[k];       
        k++;
    }
    nextMissions = new Mission[num_of_next + 1];
    k = next_pos;
    while(k < num_of_next){
        nextMissions[k] = temp[k];
        k++;
    }
    nextMissions[num_of_next] = in;
    num_of_next++;
    return;
}

void Agency::executeNextMission(){
    if(next_pos != num_of_next){
        if(nextMissions[next_pos].executeMission()){
            cash += nextMissions[next_pos].calculateProfit(ticket_price);
            //it should be added to completedMissions list/array
            if(num_of_completed == 0){
                completedMissions = new Mission;
                completedMissions[0] = nextMissions[next_pos];
                num_of_completed++;
                next_pos++;
                return;
            }
            Mission temp[num_of_completed];
            int k = 0;
            while(k < num_of_completed){
                temp[k] = completedMissions[k];       
                k++;
            }
            completedMissions = new Mission[num_of_completed + 1];
            k = 0;
            while(k < num_of_completed){
                completedMissions[k] = temp[k];
                k++;
            }
            completedMissions[num_of_completed] = nextMissions[next_pos];
            num_of_completed++;
            next_pos++;
        return;
        }
    //the mission should be moved to the end of the nextMissions list/array
    cash += nextMissions[next_pos].calculateProfit(ticket_price);
    addMission(nextMissions[next_pos]);
    next_pos++;
    cout << "Agency reschedules the mission." << endl;
    return;
    }
    else{
        cout << "No available mission to execute!" << endl;
    }
}

ostream &operator<<(ostream & out, const Agency&in){
    out << "Agency name: " << in.name << ", Total cash: " << in.cash << ", Ticket Price: " << in.ticket_price << endl;
    out << "Next Missions:" << endl;
    int i = in.next_pos;
    if(in.num_of_next != in.next_pos){
        while(i < in.num_of_next){
            cout << "Mission number: " << in.nextMissions[i].get_mission_number() << " Mission name: " << in.nextMissions[i].getName() << " Cost: " << in.nextMissions[i].get_cost() << endl;
            i++;
        }
    }
    else{
        cout << "No missions available." << endl;
    }
    out << "Completed Missions:" << endl;
    i = 0;
    if(in.num_of_completed != 0){
        while(i < in.num_of_completed){
            cout << "Mission number: " << in.completedMissions[i].get_mission_number() << " Mission name: " << in.completedMissions[i].getName() << " Cost: " << in.completedMissions[i].get_cost() << endl;
            i++;
        }
    }
    else{
        cout << "No missions completed before." << endl;
    }
    return out;
}

