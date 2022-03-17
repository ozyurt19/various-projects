/* @Author   
Student Name: Tarık Buğra Özyurt
Student ID : 150190088
Date: 10.11.2020 */
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream> 

#include "counter.h"

using namespace std;

int Counter::findindex(Token *arr,char elem[]){
	int size = Counter::token_count;
    for(int i = 0; i < size; i++){
        if(strcmp(arr[i].token, elem) == 0) return i;
    }
    return -1;
} 

bool Counter::contains(char *token, char target){
	int size = strlen(token);
	for(int i = 0; i < size; i++){
		if(token[i] == target) return true;
	}
	return false;
}

void Counter::read_and_count(){ 
	ifstream fptr;
    fptr.open("pi_approximate");
    if(!fptr){
    cerr << "Unable to open file pi_approximate!";
    exit(1);
    }
    int i = 0, temp = 0;
    struct Token tok;
    fptr.seekg(2, fptr.beg);
    while(fptr.get(tok.token, 3)){
        for(int m = 0; m < i; m++){
            if(strcmp(tok.token, Counter::token_array[m].token) == 0){
                token_array[m].count++;
                temp = 1;
            }
        }
        if(temp == 1){
            temp = 0;
            continue;
        }
        strcpy( token_array[i].token, tok.token);
        token_array[i].count++;
        i++;
    }
    fptr.clear();
    fptr.seekg(3, fptr.beg);
    while(fptr.get(tok.token, 3)){
        if(tok.token[1] == '\0') break;
        for(int m = 0; m < i; m++){
            if(strcmp(tok.token, Counter::token_array[m].token) == 0){
                token_array[m].count++;
                temp = 1;
            }
        }
        if(temp == 1){
            temp = 0;
            continue;
        }
        strcpy( token_array[i].token, tok.token);
        token_array[i].count++;
        i++;
    }
    while(Counter::token_array[Counter::token_count].count != 0){
        Counter::token_count++;
    }
    fptr.close();
}


Token *Counter::get_most_common_three(){ //burayı biraz daha sadeleştirebiliriz. belki.
	static Token arr[3];
    for(int i = 0; i < ARRAY_SIZE - 1; i++){  
        if (token_array[i].count > arr[0].count && (strcmp(token_array[i].token, arr[0].token) != 0) && (strcmp(token_array[i].token, arr[1].token) != 0) && (strcmp(token_array[i].token, arr[2].token) != 0)){
			arr[2].count = arr[1].count;  
            arr[1].count = arr[0].count;  
            arr[0].count = token_array[i].count;  
			strcpy(arr[2].token, arr[1].token);
			strcpy(arr[1].token, arr[0].token);
			strcpy(arr[0].token, token_array[i].token);
        }  
        else if (token_array[i].count > arr[1].count && (strcmp(token_array[i].token, arr[0].token) != 0) && (strcmp(token_array[i].token, arr[1].token) != 0) && (strcmp(token_array[i].token, arr[2].token) != 0)){  
            arr[2].count = arr[1].count;  
            arr[1].count = token_array[i].count; 
			strcpy(arr[2].token, arr[1].token);
			strcpy(arr[1].token, token_array[i].token);
        }
		else if (token_array[i].count > arr[2].count && (strcmp(token_array[i].token, arr[0].token) != 0) && (strcmp(token_array[i].token, arr[1].token) != 0) && (strcmp(token_array[i].token, arr[2].token) != 0)){
            arr[2].count = token_array[i].count;  
			strcpy(arr[2].token, token_array[i].token);
        }  
    } 
	return arr;
	
}
