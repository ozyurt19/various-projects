   ////////////////////////////////////
  /*      Tarık Buğra Özyurt        */
 /*          150190088             */
////////////////////////////////////

#include <iostream>
#include <fstream>
                                
#include "GreatWarrior.h"     
                             
using namespace std;

Land::Land(string name_in = "Default_land_name", string holding_in = "village"):name(name_in), holding(holding_in){}

Land::~Land(){}

Land::Land(const Land& copy):name(copy.name),holding(copy.holding){
    next = copy.next;
}



Character::Character(string name = "default_name", string land = "default_land", int manpower = 3, int gold = 20, int landnum = 0):name(name),manpower(manpower),gold(gold){
    numOfLands = landnum;
    if(numOfLands == 0){
        Land cap(land, "village");
        this->addLand(cap);
    }
    else
        numOfLands++;
}


Character::~Character(){
    /*
    while(lands){
        Land * temp = lands;
        lands = lands->next;           //i got error whatever write here actually generally when i use any delete anywhere :)
        delete temp;                     // so i just leave them empty
    }
    */
}

Character::Character(const Character& copy):manpower(copy.manpower),gold(copy.gold),numOfLands(copy.numOfLands),name(copy.name),lands(copy.lands){}

void Character::addLand(Land in){
    Land * temp = new Land;
    temp->set_name(in.get_name());
    temp->set_holding(in.get_holding());
    temp->set_next(lands);
    lands = temp;
    numOfLands += 1;
}

void Character::getTaxes(){
    Land * temp = new Land;
    temp = lands;
    int k = 0;                                      
    while(k < numOfLands){                     
        if(temp->get_holding() == "city"){
            gold += 10;
        }
        else if(temp->get_holding() == "castle"){
            gold += 7;
        }
        else if(temp->get_holding() == "village"){
            gold += 5;
        }
        else{
            cout << "Error with holding type!" << endl;
        }
        temp = temp->get_next();
        k++;
    }
}

void Character::removeLand(string land){
    Land * temp = new Land;
    temp = lands;
    int k = 0;
    if(land == lands->get_name()){
        temp = lands;
        lands = lands->get_next();
        numOfLands -= 1;
        //delete temp;
        return;
    }
    Land * rem = new Land;
    while(k < numOfLands){
        if(land == temp->get_next()->get_name()){
            rem = temp->get_next();
            temp->set_next(temp->get_next()->get_next());
            numOfLands -= 1;
            //delete rem;
            //delete temp;
            return;
        }
        temp = temp->get_next();
        k++;
    }
}



CharacterList::CharacterList(){
    characters = new Character;
    size = 0;
}

CharacterList::~CharacterList(){
    delete[] characters;
}

void CharacterList::addCharacter(Character in){
    if(size == 0){
        characters[0] = in;
        size++;
        return;
    }
    Character cp[size];
    int k = 0;
    while(k < size){
        cp[k] = characters[k];       
        k++;
    }

    characters = new Character[2 * size];
    k = 0;
    while(k < size){
        characters[k] = cp[k];
        k++;
    }
    characters[size] = in;
    size++;
}

void CharacterList::delCharacter(){
    int k = 0;
    while(k < size){
        if(characters[k].get_numoflands() == 0){
            int m = k;
            while(m < size){
                characters[m] = characters[m + 1];
                m++;
            }
            size--;
        }
        else
            k++;
    }
}


Character& CharacterList::getPlayer(string name){
    int k = 0;
    while(k < size){
        if(characters[k].get_name() == name){
            return characters[k];
        }
        k++;
    }
    return characters[k];
}

Character& CharacterList::getLandOwner(string name){
    int k = 0, m = 0;
    Land * tmp;
    while(k < size){
        m = 0;
        tmp = characters[k].get_lands();
        while(m < characters[k].get_numoflands()){
            if(tmp->get_name() == name){
                return characters[k];
            }
            tmp = tmp->get_next();
            m++;
        }
        k++;
    }
    //delete tmp;
    return characters[k];
}