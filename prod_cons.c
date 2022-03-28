#include "prod_cons.h"


//producer fn to push priority val
void add2_array(int p){
  type_arr[count] = p;
}

//consumer fn to retreive priority val
int ret_type(){
  int p,i;
  int r_ind;
  r_ind = rand() % (count-1+1)+1;
  p= type_arr[r_ind];
  for(i=r_ind;i<count;i++)
    type_arr[i] = type_arr[i+1];
  return p;
}


//produce fn to send msg to queue
void *produce(void *prod){
  int *arr = (int *)prod;
  int i,id,index,msg;
  time_t now;
  id = arr[0];
  index = arr[1];
  struct msgbuffer prod_msg;
  
  for(i=0;i<MAXITEMS;i++){
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    msg = rand();
    prod_msg.mtype = rand();
    prod_msg.mdata = msg;
  	time(&now);
    if((msgsnd(id, &prod_msg, sizeof(long)+sizeof(int)+ 1, 0))<0){
        perror("Error in msgsend");
    }
    else{
      printf("\n Item %d produced by Producer: %d at %s",msg,index,ctime(&now));
      count++;
      add2_array(prod_msg.mtype);
    }
  pthread_mutex_unlock(&mutex);
  sem_post(&full);
  
  }
}

//consume function to receive val from queue
void *consume(void *cons){
    struct msgbuffer cons_msg;
	int i,id,index,msg,type;
    int *arr = (int *)cons;
    id = arr[0];
    index = arr[1];
    for(int i=0;i<MAXITEMS;i++){
      sem_wait(&full);
      pthread_mutex_lock(&mutex); 
      type = ret_type();       //retreiving priority values
      if((msgrcv(id,&cons_msg,MAXMSG, type, 0)) == -1){
        perror("Error in message receive");
      }
      else{
        printf("\n Item %d received by Consumer: %d",cons_msg.mdata,index);
        count--;
      }
      pthread_mutex_unlock(&mutex);
      sem_post(&empty); 
    }
}

int main (int argc, char *argv[])
{
    //checking number of arguments
    int num_prod,num_cons,i;
    if(argc!=2){
    	fprintf(stderr, "usage: %s <number_of_producer/consumer pairs> \n",argv[0]);
    	num_prod = 5;				//assigning default value
    }
    else
    	num_prod = atoi(argv[1]);  //assigning user defined value
    
    int arr[2]; 		//arg for produce and consume fn
    
    num_cons = num_prod;
    pthread_t producer[num_prod],consumer[num_cons]; //producer and consumer threads
    
    //semaphore and mutex init
    pthread_mutex_init(&mutex, NULL); 
    sem_init(&empty,0,MAXITEMS);
    sem_init(&full,0,0);
    
    srand(time(0));  //seed for rand fn
    int message_queueid; //message queue id

    //message queue creation
    if((message_queueid = msgget(IPC_PRIVATE,IPC_CREAT | 0600))<0){
      perror("Error creating message queue");
      exit(-1);
    }
    
    arr[0] = message_queueid;  //passing msg queue id as one of the arg to pthread functions

    //prod and cons threads creation
    for(i=0;i<num_prod;i++){
       arr[1] = i;
       pthread_create(&producer[i], NULL, (void *)produce, (void *)arr);
    }

    for(i=0;i<num_cons;i++){
       arr[1] = i;
       pthread_create(&consumer[i], NULL, (void *)consume, (void *)arr);
    }
    for(i = 0; i < num_prod; i++) {
        pthread_join(producer[i], NULL);
    }
    for(i = 0; i < num_cons; i++) {
        pthread_join(consumer[i], NULL);
    }
    
    //destroying the message queue and sync params
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    msgctl(message_queueid,IPC_RMID,NULL); 
    return 0;
}
