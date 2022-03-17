/* @Author
Student Name: Tarık Buğra Özyurt
Student ID : 150190088
Date:  12.01.2021 */
#include <iostream>
#include <fstream> 

using namespace std;

#include "data_structs.h"  

void Stack::init(){
    head = NULL;
}

void Stack::close(){
    while(head != NULL){
        Subtask* temp = new Subtask;
        temp = head;
        head = head->next;
        delete temp;
    }
}

void Stack::push(Subtask* in){
    Subtask* temp = new Subtask;
    temp->name = in->name;
    temp->duration =  in->duration;
    temp->next = head;
    head = temp;
}

Subtask* Stack::pop(){
    Subtask* temp = new Subtask;
    temp = head;
    if(!head){
        cout << "Stack is empty." << endl;
        return temp;
    } 
    head = head->next;
    return temp;
}

bool Stack::isEmpty(){
    return head == NULL;
}

void Queue::init(){
    head = NULL;
    tail = NULL;
}

void Queue::close(){
    Process* temp = new Process;
    while(head){
        head->task_stack.close();
        temp = head;
        head = head->next;
        delete temp;
    }
}

void Queue::queue(Process* in){
    Process* temp = new Process;
    *temp = *in;
    if(head == NULL && tail == NULL){
        head = tail = temp;
        return;
    }
    tail->next = temp;
    tail = temp;
}

Process* Queue::dequeue(){
    Process* temp = new Process;
    temp = head;
    if(head == NULL){
        cout << "Queue is empty." << endl;
        return temp;
    }
    if(head == tail){
        head = tail = NULL;
    }
    else{
        head = head->next;
    }
    return temp;
}

bool Queue::isEmpty(){
    return head == NULL;
}

Process* Queue::front(){
    return head;
}

void MultiQueue::init(){
    for(int i = 0;i <= 2;i++){
        queues[i].head = NULL;
        queues[i].tail = NULL;
    }
}

void MultiQueue::close(){
    for(int i = 0; i < 3; i++){
        queues[i].close();
    }
}

void MultiQueue::queue(Process* in){
	if(in->priority == 1){
        queues[0].queue(in);
    }
    else if(in->priority == 2){
        queues[1].queue(in);
    }
    else if(in->priority == 3){
        queues[2].queue(in);
    }
}

Process* MultiQueue::dequeue(int priority){
	if(priority == 1){
        return queues[0].dequeue();
    }
    else if(priority == 2){
        return queues[1].dequeue();
    }
    else if(priority == 3){
        return queues[2].dequeue();
    }
    return queues[0].dequeue();
}

bool MultiQueue::isEmpty(){
    int i = 0;
    for(int m = 0; m < 3; m++){
        if(queues[m].head != NULL) i += 1; 
    }
    if(i == 0) return 1;

    return 0;
}

Process* MultiQueue::front(int priority){
	if(priority == 1){
        return queues[0].front();
    }
    else if(priority == 2){
        return queues[1].front();
    }
    else if(priority == 3){
        return queues[2].front();
    }
    return queues[0].front();
}








