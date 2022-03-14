#include <iostream>
#include <cstdlib>
#include <string>

#include "Person.h"     
                            
Person::Person(const string& name_in, const string& surname_in){
    name = name_in;
    surname = surname_in;
}

Passenger::Passenger(const string& name_in, const string& surname_in, int cash_in)
    :Person(name_in, surname_in){
    if(cash_in < 0){
        cash_in = 0;
        cerr << "Passenger cash can’t be negative. It is set to 0." << endl;
        }
    cash = cash_in;
}

Astronaut::Astronaut(const string& name_in, const string& surname_in, int mission_num_in):
Person(name_in, surname_in),numMissions(mission_num_in){
    if(numMissions < 0){
        numMissions = 0;
        cerr << "Number of missions that astronaut completed can't be negative. It is set to 0." << endl;
    } 
}

bool Passenger::buyTicket(int ticket_price){
    if(get_cash() >= ticket_price){
        set_cash(get_cash() - ticket_price);
        ticket = true;
        return true;
    }
    ticket = false;
    return false;
}




