//150190088 - Tarık Buğra Özyurt
#include <string>
#include <iostream>
#include <cstdlib>

#include "Orcs.h"

Orcs::Orcs(const string& name_in, int numOfUnits_in, int attack_point_in ,int health_point_in,int unit_reg_in)
:Faction(name_in,numOfUnits_in,attack_point_in ,health_point_in,unit_reg_in){}


//calls ReceiveAttack method after looking at the situation and instructions , it gives the type of the performing attack side
void Orcs::PerformAttack(){
    if(first_enemy->IsAlive() && sec_enemy->IsAlive()){
        if(first_enemy->get_type() == "Elves"){
            first_enemy->ReceiveAttack(attack_point, 70 * number_of_units / 100, "Orcs");
            sec_enemy->ReceiveAttack(attack_point, number_of_units - 70 * number_of_units / 100, "Orcs");
        }
        else{
            first_enemy->ReceiveAttack(attack_point, number_of_units - 70 * number_of_units / 100, "Orcs");
            sec_enemy->ReceiveAttack(attack_point, 70 * number_of_units / 100, "Orcs");
        }
    }
    else if(!first_enemy->IsAlive() && sec_enemy->IsAlive()){
        sec_enemy->ReceiveAttack(attack_point, number_of_units, "Orcs");
    }
    else if(first_enemy->IsAlive() && !sec_enemy->IsAlive()){
        first_enemy->ReceiveAttack(attack_point, number_of_units, "Orcs");
    }
    return;
}

//according to the instructions and taken values, it decleare dead unit number and change the number_of_units variable
//it takes type of the attacking side then modify attack point variable 
void Orcs::ReceiveAttack(int attack_p_in, int num_of_units_in, string received_type){ 
    if(received_type == "Elves") attack_p_in = 75 * attack_p_in / 100;
    else if(received_type == "Dwarves") attack_p_in = 80 * attack_p_in / 100;
    number_of_units -= num_of_units_in * attack_p_in / health_point;
    return;
}

void Orcs::Print() const{
    cout << "\"Stop running, you'll only die tired!\"" << endl; //print its own motto then calls Faction classes print method
    Faction::Print();
}

int Orcs::PurchaseWeapons(int weapon_p_in){ //increases atack point with weapon points it gets and returns taken weapon point according to the instructions
    attack_point += 2 * weapon_p_in;
    return 20 * weapon_p_in;
}   

int Orcs::PurchaseArmors(int armor_p_in){    //increases health point with armor points it gets and returns taken armor point according to the instructions
    health_point += 3 * armor_p_in;
    return 1 * armor_p_in;    
}  