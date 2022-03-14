//150190088 - Tarık Buğra Özyurt
#ifndef MERCHANT_H
#define MERCHANT_H 
#include "Faction.h"

class Merchant{
    protected:
    Faction * f_faction;
    Faction * s_faction;
    Faction * t_faction;
    int started_weapon_p;
    int started_armor_p;
    int revenue;
    int weapon_p;
    int armor_p;
    public:
    Merchant(int = 0, int = 0);
    void AssignFactions(Faction*,Faction*,Faction*);
    bool SellWeapons(string, int);
    bool SellArmors(string, int);
    void EndTurn();
    int GetRevenue(){return revenue;};  //getters
    int GetWeaponPoints(){return weapon_p;};
    int GetArmorPoints(){return armor_p;};
};

#endif