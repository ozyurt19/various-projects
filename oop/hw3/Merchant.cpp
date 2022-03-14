//150190088 - Tarık Buğra Özyurt
#include <string>
#include <iostream>
#include <cstdlib>

#include "Merchant.h"

Merchant::Merchant(int s_weapon_in, int s_armor_in):started_armor_p(s_weapon_in),started_weapon_p(s_weapon_in){
    weapon_p = s_weapon_in;
    armor_p = s_armor_in;
    revenue = 0;
}

void Merchant::AssignFactions(Faction * first,Faction * sec,Faction * third){ //assigns factions without looking at their types, 
    f_faction = first;                                                              //next functions will look at types
    s_faction = sec;
    t_faction = third;
}

bool Merchant::SellWeapons(string type_in, int weapon_p_in){ //looks to the types of factions and finds the given type then calls purchase weapons method
    if(weapon_p_in > weapon_p){
        cout << "You try to sell more weapons than you have in possession." << endl;
        return false;
    }
    if(f_faction->get_type() == type_in){
        if(!f_faction->IsAlive()){
            cout << "The faction you want to sell weapons is dead!" << endl;
            return false;
        }
        revenue += f_faction->PurchaseWeapons(weapon_p_in);
        weapon_p -= weapon_p_in;
    }
    else if(s_faction->get_type() == type_in){
        if(!s_faction->IsAlive()){
            cout << "The faction you want to sell weapons is dead!" << endl;
            return false;
        }
        revenue += s_faction->PurchaseWeapons(weapon_p_in);
        weapon_p -= weapon_p_in;
    }
    else if(t_faction->get_type() == type_in){
        if(!t_faction->IsAlive()){
            cout << "The faction you want to sell weapons is dead!" << endl;
            return false;
        }
        revenue += t_faction->PurchaseWeapons(weapon_p_in);
        weapon_p -= weapon_p_in;
    }
    cout << "Weapons sold!" << endl;
    return true;
}

bool Merchant::SellArmors(string type_in, int armor_p_in){  //looks to the types of factions and finds the given type then calls purchase armors method 
    if(armor_p_in >armor_p){
        cout << "You try to sell more armors than you have in possession." << endl;
        return false;
    }
    if(f_faction->get_type() == type_in){
        if(!f_faction->IsAlive()){
            cout << "The faction you want to sell armors is dead!" << endl;
            return false;
        }
        revenue += f_faction->PurchaseArmors(armor_p_in);
        armor_p -= armor_p_in;
    }
    else if(s_faction->get_type() == type_in){
        if(!s_faction->IsAlive()){
            cout << "The faction you want to sell armors is dead!" << endl;
            return false;
        }
        revenue += s_faction->PurchaseArmors(armor_p_in);
        armor_p -= armor_p_in;
    }
    else if(t_faction->get_type() == type_in){
        if(!t_faction->IsAlive()){
            cout << "The faction you want to sell armors is dead!" << endl;
            return false;
        }
        revenue += t_faction->PurchaseArmors(armor_p_in);
        armor_p -= armor_p_in;
    }
    cout << "Armors sold!" << endl;
    return true;
}

void Merchant::EndTurn(){  //Sets the weapon and armor points to the starting values set in the constructor
    weapon_p = started_weapon_p;
    armor_p = started_armor_p;
}

