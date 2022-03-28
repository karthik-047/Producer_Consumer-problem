#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXITEMS 5
#define MAXMSG 512

pthread_mutex_t mutex;
sem_t full;
sem_t empty;

//global counter for number of elts
int count=0;

//array for storing priorities
int type_arr[10];

//message structure
struct msgbuffer{
  long mtype;
  int mdata;
};

//helper functions
void add2_array(int);
int ret_type();
