//150190088 - Tarık Buğra Özyurt
#ifndef ORCS_H
#define ORCS_H 
#include "Faction.h"

class Orcs:public Faction{   //got all of the Faction classes properties and itselfs
    public:
    Orcs(const string& = "default_name", int = 0,int = 0,int = 0,int = 0);
    void PerformAttack();      
    void ReceiveAttack(int,int, string);     
    int PurchaseWeapons(int);     
    int PurchaseArmors(int);   
    void Print() const;
    string get_type(){return "Orcs";}; //type getter
};

#endif

