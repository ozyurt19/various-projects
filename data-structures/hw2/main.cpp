/* @Author
Student Name: Tarık Buğra Özyurt
Student ID : 150190088
Date: 9.12.2020 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <string.h>
#include <fstream> 
#include <iomanip>

using namespace std;

struct resistor{
char group;
double value;
int quantity;
resistor *next;
};

struct circuit{
resistor *head;
resistor *for_print;
void create();
void add_resistor(char, double);
void add_resistor_value(char, double);
int remove_resistor(char, int);
int remove_resistor_value(char, int);
void delete_resistor(char);
void delete_resistor_value(char);
void circuit_info();
void clear();
};

//Creates the circuit(resistor list).
void circuit::create(){
    head = new resistor;
    head = NULL;
    for_print = new resistor;
    for_print = NULL;
} 

//swaps two resistor.
void my_swap(resistor * res1, resistor * res2){
    resistor* tmp;
    tmp = new resistor;
    tmp->next = NULL;
    tmp->group = res1->group;
    tmp->value = res1->value;
    tmp->quantity = res1->quantity;
    res1->group = res2->group;
    res1->value = res2->value;
    res1->quantity = res2->quantity;
    res2->group = tmp->group;
    res2->value = tmp->value;
    res2->quantity = tmp->quantity;
}

//sorts linked list with bubble method, in alphabetically ascending order
void bubble_sort_alphabetical(resistor *head)
{
	int swapped;
	resistor *lPtr; 
	resistor *rPrt = NULL; 
	do{	
		swapped = 0;
		lPtr = head;
		while(lPtr->next != rPrt){
			if (lPtr->group > lPtr->next->group) {
				my_swap(lPtr, lPtr->next); 
                swapped = 1; 
			}
			lPtr = lPtr->next;
		}
		rPrt = lPtr;
	}while(swapped);
}

//sorts linked list with bubble method, in ascending order by resistor value
void bubble_sort_value(resistor *head)
{
	int swapped;
	resistor *lPtr; 
	resistor *rPrt = NULL; 
	do{	
		swapped = 0;
		lPtr = head;
		while(lPtr->next != rPrt){
			if (lPtr->value > lPtr->next->value) {
				my_swap(lPtr, lPtr->next); 
                swapped = 1; 
			}
			lPtr = lPtr->next;
		}
		rPrt = lPtr;
	}while(swapped);
}

//Adds a resistor to the circuit (workflow 1).
void circuit::add_resistor(char grp, double val){    
    resistor* tmp;
    tmp = new resistor;
    tmp = head;
    while(tmp != NULL){
        if(tmp->group == grp){
            tmp->quantity += 1;
            return;
        }
        tmp = tmp->next;
    }
    resistor* new_res;
    new_res = new resistor;
    new_res->next = NULL;
    new_res->value = val;
    new_res->group = grp;
    new_res->quantity = 1;
    if(head == NULL){
        head = new_res;
        return;
    }
    new_res->next = head;  
    head = new_res;
    bubble_sort_alphabetical(head);  
    return;
} 

//Adds a resistor to the circuit (workflow 1), for the value ordered linked list.
void circuit::add_resistor_value(char grp, double val){    
    resistor* tmp;
    tmp = new resistor;
    tmp = for_print;
    while(tmp != NULL){
        if(tmp->value == val){
            tmp->quantity += 1;
            return;
        }
        tmp = tmp->next;
    }
    resistor* new_res;
    new_res = new resistor;
    new_res->next = NULL;
    new_res->value = val;
    new_res->group = grp;
    new_res->quantity = 1;
    if(for_print == NULL){
        for_print = new_res;
        return;
    }
    new_res->next = for_print;  
    for_print = new_res;
    bubble_sort_value(for_print);  
    return;
} 

//Removes a resistor from the circuit.
int circuit::remove_resistor(char grp, int val){
    resistor* tmp;
    tmp = new resistor;
    tmp = head;
    int i = 0;
    while(tmp != NULL){
        if(tmp->group == grp && tmp->value == (-1 * val)){
            i = 1;
            if(tmp->quantity != 1){
                tmp->quantity -= 1;
                return 0;
            }
            else{
                circuit::delete_resistor(grp);
                return 0;
            }
        }
        tmp = tmp->next;
    }
    if(i == 0){
        cout << "NO_RESISTOR" << endl;
    }
    return 0;
}


//Removes a resistor from the circuit, for the linked list with value ordered.
int circuit::remove_resistor_value(char grp, int val){
    resistor* tmp;
    tmp = new resistor;
    tmp = for_print;
    while(tmp != NULL){
        if(tmp->group == grp && tmp->value == (-1 * val)){
            if(tmp->quantity != 1){
                tmp->quantity -= 1;
                return 0;
            }
            else{
                circuit::delete_resistor_value(grp);
                return 0;
            }
        }
        tmp = tmp->next;
    }
    return 0;
}

//It deletes the resistor node from the circuit.
void circuit::delete_resistor(char grp){
    resistor* tmp;
    tmp = new resistor;
    tmp = head;
    while (tmp != NULL){
        if(tmp->next->group == grp){           
            tmp->next = tmp->next->next;           
            return;
        }
        tmp = tmp->next;
    }
    return;  
} 

//It deletes the resistor node from the circuit, for the linked list with value ordered.
void circuit::delete_resistor_value(char grp){
    resistor* tmp;
    tmp = new resistor;
    tmp = for_print;
    while (tmp != NULL){
        if(tmp->next->group == grp){           
            tmp->next = tmp->next->next;           
            return;
        }
        tmp = tmp->next;
    }
    return;
    
} 

//Prints the resistor info and total resistance in the circuit (workflow 3).
void circuit::circuit_info(){
    resistor* tmp1;
    tmp1 = new resistor;
    tmp1 = for_print;
    resistor* tmp2;
    tmp2 = new resistor;
    tmp2 = head;
    double sum = 0;

    while(tmp2 != NULL){
        sum += (tmp2->value) / (tmp2->quantity);
        tmp2 = tmp2->next;
    }
    while(tmp1 != NULL){
        cout << tmp1->value << ":" << tmp1->quantity << endl;
        tmp1 = tmp1->next;
    }
    
    cout << "Total resistance=" << sum << " ohm" << endl;
}

//Deletes all of the nodes of the list (workflow 4).
void circuit::clear(){
    resistor* del;
    del = new resistor;
    del = for_print;
    while(for_print != NULL){
        del = for_print;
        for_print = for_print->next;;
        delete del;
    }
    del = head;
    while(head != NULL){
        del = head;
        head = head->next;;
        delete del;
    }
}

int main(int argc, char *argv[]){
    struct circuit circ;
    circ.create();
    ifstream input (argv[1]);
    if(argc != 2){
        cout<<"Need executable input file!";
        exit(1);
    }
    if(!input.is_open()){
        cout<<"Unable to open file!";
    }
    char grp;
    double val;
    char c;
    while (input >> c)
    {
    grp = c;
    input >> val;
    if(val > 0){
        circ.add_resistor(grp, val);
        circ.add_resistor_value(grp, val);
    }
    if(val < 0){
        circ.remove_resistor(grp, val);
        circ.remove_resistor_value(grp, val);
    }
    if(val == 0)
        circ.circuit_info();
    } 

    input.close();
    circ.clear();
    return 0;
}


