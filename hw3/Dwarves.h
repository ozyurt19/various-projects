//150190088 - Tarık Buğra Özyurt
#ifndef DWARVES_H
#define DWARVES_H 
#include "Faction.h"

class Dwarves:public Faction{    //got all of the Faction classes properties and itselfs
    public:
    Dwarves(const string& = "default_name", int = 0,int = 0,int = 0,int = 0);
    void PerformAttack();      
    void ReceiveAttack(int,int, string);     
    int PurchaseWeapons(int);     
    int PurchaseArmors(int);   
    void Print() const;
    string get_type(){return "Dwarves";}; //type getter
};

#endif

