   ////////////////////////////////////
  /*      Tarık Buğra Özyurt        */
 /*          150190088             */
////////////////////////////////////

#include <iostream>
#include <fstream>
#include <time.h>

#include "GreatWarrior.h"
#include "GreatWarrior.cpp"

using namespace std;
/*	Define necessary classes and attributes in GreatWarrior.h and GreatWarrior.cpp */

/*	= Fill in the blanks in this main.cpp file. The parts that you need to implemented are specified below.
    = Please write your code between ///// FILL HERE ///// lines.
    = The expressions you need to print out with cout operation are given in necessary format.
    = You can use them directly by filling the variable parts.
*/

void listCharacters(CharacterList&);
void listLands(CharacterList&);
void readData(string, CharacterList&);
void printGameMenu();
bool endOfTurn(Character&, int);

int main() {
    cout << "Welcome to the Great Warriors. Create your character and attack other lands to be a great warrior.\n" << endl;
    
    CharacterList charList;             // list object to store the characters

    string fileName = "characters.txt"; // read characters.txt file
    readData(fileName, charList);

    /* creating player's character */
    string name, land, general;
    cout << "Enter your name: ";
    cin >> name;

    cout << "Enter name of your capital: ";
    cin >> land;

    cout << "Enter name of your general: ";
    cin >> general;


    ///// FILL HERE /////

    /*  Create your constant general object and your own character object,
        then add your character into characters list */
    const Character my_general(general, "", 0,0,0);
    Character myCharacter(name, land, 3, 20, 0);   
    charList.addCharacter(myCharacter);

    ///// FILL HERE /////


    // In-game loop 
    int choice = 0, round = 0;
    while (choice != 6) {
        printGameMenu();

        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "You have rested in your palace." << endl;
            cout << "You've talked with your general " << my_general.get_name() << "." << endl;

            round++;
            break;
        }
        case 2: {
            listLands(charList);
            cout << "Enter name of the land to attack." << endl;

            string land;
            cin >> land;

            ///// FILL HERE /////

            /*	Get the attacked player and execute the attack considering the manpower each side has:

                -	If you won, attacked side will lose all manpower and the attacked land will be yours. 
                    You will also lose some manpower (as much as attacked lose).
                    Print this: cout << "You've won the battle and conquered " << land << "." << endl;

                -	If you lose, you will lose all your manpower.
                    Print this: cout << "You've lost the battle and " << __number of manpower you lost__ << " manpower." << endl;
            */
            if(charList.getLandOwner(land).get_manpower() <= charList.getPlayer(name).get_manpower()){
                charList.getPlayer(name).set_manpower(charList.getPlayer(name).get_manpower() - charList.getLandOwner(land).get_manpower());
                charList.getLandOwner(land).set_manpower(0);

                Land * tmp = new Land;                                    //new Land * to traverse
                tmp = charList.getLandOwner(land).get_lands();
                while(tmp->get_name() != land){
                    tmp = tmp->get_next();                       //finding which one need to be conquered
                }
                Land l;                                          //new Land to get the info of tmp and add with addLand to our Character
                l.set_name(tmp->get_name());
                l.set_holding(tmp->get_holding());
                l.set_next(tmp->get_next());

                charList.getPlayer(name).addLand(l);                     //adding conquered Land
                charList.getLandOwner(land).removeLand(land);              //deleting it from attacked side
                charList.delCharacter();                                    //function automatically traverse and look if some character has 0 land
                cout << "You've won the battle and conquered " << land << "." << endl;
            }
            else{     //if i lost i do not need to change the manpower of attacked side
                //charList.getLandOwner(land).set_manpower(charList.getLandOwner(land).get_manpower() - charList.getPlayer(name).get_manpower());
                cout << "You've lost the battle and " << charList.getPlayer(name).get_manpower() << " manpower." << endl;
                charList.getPlayer(name).set_manpower(0);
            }
            ///// FILL HERE /////

            round++;
            break;
        }
        case 3:
            cout << "How much manpower do you need? (1 manpower=5 gold)" << endl;

            int order;
            cin >> order;

            ///// FILL HERE /////

            /* Check if you have enough money to get the requested manpower:

                - 	If you have, you got the manpower you want.
                    Print this: cout << "Order successful. You have " << __number of manpower you have after purchase__ << " manpower." << endl;

                -	If you do not, print this: cout << "You do not have enough money." << endl;
            */

            if(order * 5 > charList.getPlayer(name).get_gold()){
                cout << "You do not have enough money." << endl;
            }
            else{
                charList.getPlayer(name).set_gold(charList.getPlayer(name).get_gold() - 5 * order);
                charList.getPlayer(name).set_manpower(charList.getPlayer(name).get_manpower() + order);
                cout << "Order successful. You have " << charList.getPlayer(name).get_manpower() << " manpower." << endl;
            }
            ///// FILL HERE /////

            round++;
            break;
        case 4:
            listCharacters(charList);
            break;
        case 5:
            listLands(charList);
            break;
        case 6:
            return 0;
        default:
            cout << "You entered an invalid value. Try again." << endl;
        }

        ///// FILL HERE /////

        /*	Check if the game is over in two cases:

            -	Call the endOfTurn function which is defined below in the code.
                endOfTurn function executes the necessary end of turn process and
                returns a bool value which indicates if you can continue the game or not.

            -	Terminate the program if you are the only great warrior left.
                Print this: cout << __your player name__ << " is the only great warrior now." << endl;
        */
       if((choice == 1 || choice == 2|| choice == 3)){
           bool boolean = endOfTurn(charList.getPlayer(name), round);
            if(charList.get_size() == 1){
                cout << myCharacter.get_name() << " is the only great warrior now." << endl;
                return 0;
            }
            if(!boolean) return 0;
        }
        if(charList.get_size() == 1){
                cout << myCharacter.get_name() << " is the only great warrior now." << endl;
                return 0;
            }
        ///// FILL HERE /////
    }
}

void readData(string fileName, CharacterList& charList) {

    fstream dataFile(fileName.c_str());
    if (dataFile.is_open()) {
        string word;
        while (dataFile >> word) {

            string name, title;
            int money, manpower, numOfLands;

            name = word;
            dataFile >> manpower;
            dataFile >> money;
            dataFile >> numOfLands;

            ///// FILL HERE /////
            /* Create a new character with read data */
            Character new_char(name, "default", manpower, money, -1);  
            ///// FILL HERE /////
            string landName, holding;
            for (int i = 0; i < numOfLands; i++) {
                dataFile >> landName;
                dataFile >> holding;

                ///// FILL HERE /////

                /* Create a new land object with read data and assign the land to the character you have created */

                Land newLand(landName, holding);
                new_char.addLand(newLand);
                ///// FILL HERE /////
            }

            ///// FILL HERE /////
            
            /* Add the character into character list */
            charList.addCharacter(new_char);
            ///// FILL HERE /////

        }

        dataFile.close();
    }
    else cout << "Unable to open the file" << endl;

    return;
}

void printGameMenu() {
    cout << endl;
    cout << "1. Stay in your palace" << endl;
    cout << "2. Attack to a land" << endl;
    cout << "3. Buy manpower" << endl;
    cout << "4. List characters" << endl;
    cout << "5. List lands" << endl;
    cout << "6. Exit" << endl;
    cout << endl;
}

void listCharacters(CharacterList& charList) {
    cout << endl;

    ///// FILL HERE /////

    /* Print out the names of each character in character list in a loop */
    int k = 0;
    while(k < charList.size){
        cout << charList.characters[k].get_name() << endl;
        k++;
    }
    ///// FILL HERE /////

}

void listLands(CharacterList& charList) {
    cout << endl;

    ///// FILL HERE /////

    /*	Loop over each character in characters list and print out their lands in following format:
        cout << __name of land__ << " " << __type of land__ << " owned by " << __name of player__ << endl;
        (i.e. Gotham city owned by Batman)
    */
    int k = 0;
    int m = 0;
    Land * tmp = new Land;
    while(k < charList.size){
        m = 0;
        tmp = charList.characters[k].get_lands();
        while(m < charList.characters[k].get_numoflands()){
            cout << tmp->get_name() << " " << tmp->get_holding() << " owned by " << charList.characters[k].get_name() << endl;
            tmp = tmp->get_next();
            m++;
        }
        k++;
    }
    //delete tmp;

    ///// FILL HERE /////

    cout << endl;
}

bool endOfTurn(Character& player, int round) { //return a bool value that indicates if the game is over or not.

    ///// FILL HERE /////

    /* End of turn evaluations:
        -	Collect taxes and feed soldiers

        -	Check the number of lands you have and if you do not have any lands left, the game is over
            Print this:	cout << "You are no longer a great warrior. You survived " << round << " turns." << endl;
                        cout << endl;
                        cout << "GAME OVER." << endl;

        -	Check the number of manpower you have and if you do not have any manpower left, you lose one of your lands randomly.
            Print this:	cout << "You lost one of your lands to rebellions since you don't have enough army." << endl;

        -	Check the amount of money you have, if you do not have enough money to feed your soldiers you lose
            the soldiers that you cannot feed. 1 gold for each soldier is needed. If you have 5 gold and 6 soldiers 1 soldier will
            run away from your army.
            Print this: cout << __number of runaway soldiers__ << " soldiers run away from your army because you don't have enough gold to feed them." << endl;

        -	At last, print your status in the following format:
            cout << "Turn " << round << ": " << " " << __name of your player__ << " has " << __number of lands you have__
        << " land(s), " << __number of manpower you have__ << " manpower and " << __number of golds you have__ << " golds." << endl;
    */
    
    player.getTaxes();
    player.set_gold(player.get_gold() - player.get_manpower());
    if(player.get_numoflands() == 0){
        cout << "You are no longer a great warrior. You survived " << round << " turns." << endl;
        cout << endl;
        cout << "GAME OVER." << endl;
        return false;
    }
    if(player.get_manpower() == 0){
        srand(time(0));
        int random = rand() % player.get_numoflands();
        Land * temp = player.get_lands();
        int i = 0;
        while(i < random){
            temp = temp->get_next();
            i++;
        }
        player.removeLand(temp->get_name());
        delete temp;
        cout << "You lost one of your lands to rebellions since you don't have enough army." << endl;
    }
    if(player.get_gold() < player.get_manpower()){
        int d = player.get_manpower() - player.get_gold();
        player.set_manpower(player.get_manpower() - d);
        cout << d << " soldiers run away from your army because you don't have enough gold to feed them." << endl;
    }
    cout << "Turn " << round << ": " << " " << player.get_name() << " has " << player.get_numoflands()
        << " land(s), " << player.get_manpower() << " manpower and " <<player.get_gold() << " golds." << endl;
        return true;
    ///// FILL HERE /////

}
