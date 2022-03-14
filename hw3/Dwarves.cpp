//150190088 - Tarık Buğra Özyurt
#include <string>
#include <iostream>
#include <cstdlib>

#include "Dwarves.h"

Dwarves::Dwarves(const string& name_in, int numOfUnits_in, int attack_point_in ,int health_point_in,int unit_reg_in)
:Faction(name_in,numOfUnits_in,attack_point_in ,health_point_in,unit_reg_in){}

//calls ReceiveAttack method after looking at the situation and instructions , it gives the type of the performing attack side
void Dwarves::PerformAttack(){
    if(first_enemy->IsAlive() && sec_enemy->IsAlive()){
        first_enemy->ReceiveAttack(attack_point, number_of_units * 1/2, "Dwarves");
        sec_enemy->ReceiveAttack(attack_point, number_of_units - number_of_units * 1/2, "Dwarves");
    }
    else if(!first_enemy->IsAlive() && sec_enemy->IsAlive()){
        sec_enemy->ReceiveAttack(attack_point, number_of_units, "Dwarves");
    }
    else if(first_enemy->IsAlive() && !sec_enemy->IsAlive()){
        first_enemy->ReceiveAttack(attack_point, number_of_units, "Dwarves");
    }
    return;
}

//according to the instructions and taken values, it decleare dead unit number and change the number_of_units variable
//it takes type of the attacking side then modify attack point variable 
void Dwarves::ReceiveAttack(int attack_p_in, int num_of_units_in, string received_type){
    number_of_units -= num_of_units_in * attack_p_in / health_point;
    return;
}

void Dwarves::Print() const{  //print its own motto then calls Faction classes print method
    cout << "\"Taste the power of our axes!\"" << endl;
    Faction::Print();
}

int Dwarves::PurchaseWeapons(int weapon_p_in){ //increases atack point with weapon points it gets and returns taken weapon point according to the instructions
    attack_point += weapon_p_in;
    return 10 * weapon_p_in;
}   

int Dwarves::PurchaseArmors(int armor_p_in){   //increases health point with armor points it gets and returns taken armor point according to the instructions
    health_point += 2 * armor_p_in;
    return 3 * armor_p_in;
}  