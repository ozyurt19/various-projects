/* @Author
Student Name: Tarık Buğra Özyurt
Student ID : 150190088
Date:  12.01.2021 */
#include <iostream>
#include <fstream> 

using namespace std;   

#include "data_structs.h"

int main(int argc, char *argv[]){
    ifstream input (argv[1]);//opening data file
    if(argc != 2){
        cout << "Need executable input file!" << endl;
        exit(1);
    }
    if(!input.is_open()){
        cout << "Unable to open file!" << endl;
    }
    Queue q;
    q.init();
    Subtask * data_subtask = new Subtask;
    Process * data_process = new Process;
    data_process->task_stack.init();
    while (input >> data_process->name){ //reading data to a queue
        input >> data_process->priority;
        input >> data_process->arrival_time;
        input >> data_process->task_count;
        data_process->deadline = data_process->arrival_time;
        for(int m = 0; m < data_process->task_count; m++){//reading subtasks
            input >> data_subtask->name;
            input >> data_subtask->duration;
            data_process->deadline += data_subtask->duration;
            data_process->task_stack.push(data_subtask);
        }
        q.queue(data_process);          
        data_process->task_stack.init();
    }
    data_process->task_stack.close();
    delete data_subtask;
    delete data_process;
    int time = 0;
    int special = 0;
    int lateness = 0;
    MultiQueue mq;
    mq.init();
    mq.queue(q.head);
    q.dequeue();
    while(!mq.isEmpty() || !q.isEmpty()){ 

        again:
        if(!q.isEmpty() && q.head->arrival_time == time){
            mq.queue(q.head);
            q.dequeue();
            goto again;
        } 

        if(mq.queues[2].isEmpty() && special == 2){
            special = 0;
        }
        if(!mq.queues[0].isEmpty()){ //operations for priority 1
            int in_time = time;
            in_time += mq.queues[0].head->task_stack.head->duration;
            while(time <= in_time){
                if(!q.isEmpty() && q.head->arrival_time == time){
                mq.queue(q.head);             
                q.dequeue();
                } 
                else{
                    time++;
                }  
            } 
            time -= 1;
            cout << mq.queues[0].head->name << " " << mq.queues[0].head->task_stack.pop()->name << endl;
            if(mq.queues[0].head->task_stack.isEmpty()){
                lateness += time;
                lateness -= mq.queues[0].head->deadline;
                mq.queues[0].dequeue();
            }
        }

        else if(!mq.queues[1].isEmpty() && special != 2){   //operations for priority 2
            int in_time = time;
            in_time += mq.queues[1].head->task_stack.head->duration;
            while(time <= in_time){
                if(!q.isEmpty() && q.head->arrival_time == time){
                mq.queue(q.head);
                q.dequeue(); 
                } 
                else{
                    time++;
                }              
            }
            time -= 1;
            cout << mq.queues[1].head->name << " " << mq.queues[1].head->task_stack.pop()->name << endl;
            if(mq.queues[1].head->task_stack.isEmpty()){
                lateness += time;
                lateness -= mq.queues[1].head->deadline;
                mq.queues[1].dequeue();
            }
            special += 1;
        } 

        else if(!mq.queues[2].isEmpty()){    //operations for priority 3
            int in_time = time;
            in_time += mq.queues[2].head->task_stack.head->duration;
            while(time <= in_time){
                if(!q.isEmpty() && q.head->arrival_time == time){
                mq.queue(q.head);
                q.dequeue();
                } 
                else{
                    time++;
                }  
            }
            time -= 1;
            cout << mq.queues[2].head->name << " " << mq.queues[2].head->task_stack.pop()->name << endl;
            if(mq.queues[2].head->task_stack.isEmpty()){
                lateness += time;
                lateness -= mq.queues[2].head->deadline;
                mq.queues[2].dequeue();
            }
            if(special == 2){
                special = 0;
            }
        } 
        else{
            time++;
        }
    }
    cout << "Cumulative Lateness: " << lateness << endl;
    q.close();
    mq.close();
    return 0;
}