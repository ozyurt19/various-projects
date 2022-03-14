//150190088 - Tarık Buğra Özyurt
#include <string>
#include <iostream>
#include <cstdlib>

#include "Elves.h"

Elves::Elves(const string& name_in, int numOfUnits_in, int attack_point_in ,int health_point_in,int unit_reg_in)
:Faction(name_in,numOfUnits_in,attack_point_in ,health_point_in,unit_reg_in){}

//calls ReceiveAttack method after looking at the situation and instructions , it gives the type of the performing attack side
void Elves::PerformAttack(){
    if(first_enemy->IsAlive() && sec_enemy->IsAlive()){
        if(first_enemy->get_type() == "Dwarves"){
            first_enemy->ReceiveAttack(40 * number_of_units / 100, 150 * attack_point / 100, "Elves");
            sec_enemy->ReceiveAttack(60 * number_of_units / 100, attack_point, "Elves");
        }
        else{
            first_enemy->ReceiveAttack(60 * number_of_units / 100, attack_point, "Elves");
            sec_enemy->ReceiveAttack(40 * number_of_units / 100, 150 * attack_point / 100, "Elves");
        }      
    }
    else if(!first_enemy->IsAlive() && sec_enemy->IsAlive()){
        if(sec_enemy->get_type() == "Dwarves") sec_enemy->ReceiveAttack(number_of_units, 150 * attack_point / 100, "Elves");
        else sec_enemy->ReceiveAttack(number_of_units, attack_point, "Elves");
    }
    else if(first_enemy->IsAlive() && !sec_enemy->IsAlive()){
        if(first_enemy->get_type() == "Dwarves") first_enemy->ReceiveAttack(number_of_units, 150 * attack_point / 100, "Elves");
        else first_enemy->ReceiveAttack(number_of_units, attack_point, "Elves");
    }
    return;
}

//according to the instructions and taken values, it decleare dead unit number and change the number_of_units variable
//it takes type of the attacking side then modify attack point variable 
void Elves::ReceiveAttack(int attack_p_in, int num_of_units_in, string received_type){
    if(received_type == "Orcs") attack_p_in = 125 * attack_p_in / 100;
    else if(received_type == "Dwarves") attack_p_in = 75 * attack_p_in / 100;
    number_of_units -= num_of_units_in * attack_p_in / health_point;
    return;
}

void Elves::Print() const{   //print its own motto then calls Faction classes print method
    cout << "\"You cannot reach our elegance.\"" << endl;  
    Faction::Print();
}

int Elves::PurchaseWeapons(int weapon_p_in){  //increases atack point with weapon points it gets and returns taken weapon point according to the instructions
    attack_point += 2 * weapon_p_in;
    return 15 * weapon_p_in;
}   

int Elves::PurchaseArmors(int armor_p_in){ //increases health point with armor points it gets and returns taken armor point according to the instructions
    health_point += 4 * armor_p_in;
    return 5 * armor_p_in;
}  

