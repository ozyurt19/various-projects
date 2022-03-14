//150190088 - Tarık Buğra Özyurt
#include <string>
#include <iostream>
#include <cstdlib>

#include "Faction.h"

Faction::Faction(const string& name_in, int numOfUnits_in, int attack_point_in ,int health_point_in,int unit_reg_in)
:name(name_in),number_of_units(numOfUnits_in),attack_point(attack_point_in),health_point(health_point_in),unit_regeneration_number(unit_reg_in){
    total_health = number_of_units * health_point; 
    is_alive = true;
    first_enemy = 0;
    sec_enemy = 0;
}

void Faction::AssignEnemies(Faction * first,Faction * second){ //assigns enemies wtihout looking at their types, 
    first_enemy = first;                                         //other functions will look at their types
    sec_enemy = second;
}

void Faction::Print() const{
    cout << "Faction Name:         " << name << endl;
    cout << "Status:               ";
    if(is_alive) cout << "Alive" << endl; 
    else cout << "Defeated" << endl;
    cout << "Number of Units:      " << number_of_units << endl;
    cout << "Attack Point:         " << attack_point << endl;
    cout << "Health Point:         " << health_point << endl;
    cout << "Unit Regen Number:    " << unit_regeneration_number << endl;
    cout << "Total Faction Health: " << total_health << endl;
}

void Faction::EndTurn(){   //increases unit number and chech if it is alive then calculate total health at the end of every turn
    if(number_of_units < 0) number_of_units = 0;
    if(number_of_units == 0) is_alive = false;
    if(number_of_units != 0) number_of_units += unit_regeneration_number;
    total_health = number_of_units * health_point; 
}