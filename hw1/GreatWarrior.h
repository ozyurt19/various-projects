   ////////////////////////////////////
  /*      Tarık Buğra Özyurt        */
 /*          150190088             */
////////////////////////////////////

#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Land{
    string name;
    string holding;
    Land * next;
    public:
    Land(string, string);
    ~Land();
    Land(const Land &);
    inline string get_name(){return name;};
    inline string get_holding(){return holding;};
    inline Land * get_next(){return next;};
    inline void set_name(string in){name = in;};
    inline void set_holding(string in){holding = in;};
    inline void set_next(Land * in){next = in;};
};

class Character{
    string name; 
    int manpower;
    int gold;
    int numOfLands;
    Land * lands;
    public:
    Character(string, string, int, int, int);
    ~Character();
    Character(const Character &);
    void addLand(Land);
    void getTaxes();
    void removeLand(string);
    inline string get_name() const {return name;};
    inline int get_manpower(){return manpower;};
    inline int get_gold(){return gold;};
    inline int get_numoflands(){return numOfLands;};
    inline Land * get_lands(){return lands;};
    inline void set_manpower(int in){manpower = in;};
    inline void set_gold(int in){gold = in;};
};

class CharacterList{
    int size;
    Character * characters;
    friend void listLands(CharacterList&);
    friend void listCharacters(CharacterList&);
    public:
    CharacterList();
    ~CharacterList();
    void addCharacter(Character);
    void delCharacter();
    Character& getPlayer(string);
    Character& getLandOwner(string);
    inline int get_size(){return size;};
};