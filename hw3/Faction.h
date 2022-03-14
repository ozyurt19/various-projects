//150190088 - Tarık Buğra Özyurt
using namespace std;
#include <string>

#ifndef FACTION_H
#define FACTION_H 

class Faction{  //parent class for other three character classes it has some pure virtual functions 
    protected:
    string name;
    Faction * first_enemy;
    Faction * sec_enemy;
    int number_of_units;
    int attack_point;
    int health_point;
    int unit_regeneration_number;
    int total_health;
    bool is_alive;
    public:
    Faction(const string& = "default_name", int = 0,int = 0,int = 0,int = 0);
    void AssignEnemies(Faction*,Faction*);        
    virtual void PerformAttack() = 0;                 //pure virtual methods
    virtual void ReceiveAttack(int, int, string) = 0;     //they are equal to zero
    virtual int PurchaseWeapons(int) = 0;                 
    virtual int PurchaseArmors(int) = 0;      
    virtual void Print() const;                  
    void EndTurn();
    bool IsAlive(){return is_alive;};
    virtual string get_type() = 0; //type getter returns a string for its type
};

#endif