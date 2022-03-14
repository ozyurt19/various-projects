//150190088 - Tarık Buğra Özyurt
#ifndef ELVES_H
#define ELVES_H 
#include "Faction.h"

class Elves:public Faction{ //got all of the Faction classes properties and itselfs
    public:
    Elves(const string& = "default_name", int = 0,int = 0,int = 0,int = 0);
    void PerformAttack();      
    void ReceiveAttack(int,int, string);     
    int PurchaseWeapons(int);     
    int PurchaseArmors(int);   
    void Print() const;
    string get_type(){return "Elves";}; //type getter
};

#endif