#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep()
#include <pthread.h>        //thread header file
int nr;
int h = 0;      //global variable keeping track of every registration
int s = 0;     //global variable keeping track of every interview
int * arr;       //array that stores interview times we readed from text file
int * regarr; //array that we will use to keep track of registrastion to know when to start interviewing
pthread_mutex_t lock;
pthread_mutex_t lock2;

// normal C functions that is executed as a thread 
// when its name is specified in pthread_create()
void *registering(void *in)
{   
    int n = *(int * )in;  //cast the address to the value of number of applicants
    while(h < n){
        pthread_mutex_lock(&lock2);
        sleep(nr);              //after every nr seconds it prints massage and makes regarr's hth element 1 for
        printf("Applicant %d's registration is done\n", h + 1); //interview function to call for that applicant 
        regarr[h] = 1;
        h += 1;
        pthread_mutex_unlock(&lock2);
    }
    return NULL;
}

void *interview(void *in)
{
    int l;
    long i;
    i = (long)in;
    while(arr[s] != -1){
        pthread_mutex_lock(&lock);
        if(regarr[s] == 0) sleep(nr); //if applicant did not registered yet wait nr seconds
        s++;            
        l = s - 1; 
        printf("Interviewer %ld started interview with Applicant %d\n", i, l + 1);
        pthread_mutex_unlock(&lock);
        sleep(arr[l]);
        printf("Interviewer %ld finished interview with Applicant %d\n", i, l + 1);
    }
    return NULL;
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Commandline argument fail.\n");
        return 1;
    } 
    if (pthread_mutex_init(&lock, NULL) != 0)  //command line argument and mutex initializations
    {
        printf("Mutex initialization failed.\n");
        return 1;
    }
    if (pthread_mutex_init(&lock2, NULL) != 0)
    {
        printf("Mutex initialization failed.\n");
        return 1;
    }
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    pthread_t recepcionist; //out threads
    pthread_t interviewers1; 
    pthread_t interviewers2; 
    pthread_t interviewers3; 

    fp = fopen("file.txt", "r"); // opening text file
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int c = 0;
    arr = (int*) malloc(1 * sizeof(int)); //originally has 1 memory space of sizeof(int)
    while ((read = getline(&line, &len, fp)) != -1) {
        arr = (int*) realloc(arr, 1 * sizeof(int)); //we reallocate it every step
        c++;
        arr[c - 1] = atoi(line);      //storing every line in arr array
    }
    arr[c] = -1;
    regarr = (int*) calloc(c, sizeof(int));

    
    for(int m = 0; m < 4; m++){
        printf("Applicant %d applied to the receptionist\n", m + 1); //they are applying and then after they register 
    }                                                                 //process continue

    nr = atoi(argv[1]); //taking commanline argument and storing in nr variable
    pthread_create(&recepcionist, NULL, registering, &c);               //creating threads this one takes number of applicants 
                                                                            //as argument of their functions
    pthread_create(&interviewers1, NULL, interview, (void *)1);//these are taking interviewer numbers as argument 
    pthread_create(&interviewers2, NULL, interview, (void *)2);                                  //of their functions
    pthread_create(&interviewers3, NULL, interview, (void *)3);
    
    pthread_join(recepcionist, NULL); //in the end calling pthread_join to make program to wait till every thread finishes
    pthread_join(interviewers1, NULL);
    pthread_join(interviewers2, NULL);
    pthread_join(interviewers3, NULL);
    printf("All applicants have interviewed successfully.");
    pthread_exit(NULL);
    fclose(fp);
    if (line)
        free(line);
    free(arr);
    free(regarr);
    
    exit(0);
}