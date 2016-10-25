#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
//#define NUM 4

static int NUM=8;
static long long int number_of_toss;
int *result;
long long int number_in_circle=0;
pthread_mutex_t mutex;
FILE *fp;    
int *threadresult;

void *func(void *i){
    int toss=0;
    int seed=rand();
    int thread=(int)i;
    double dist;
    double x,y;
    int ranx,rany;
    for(toss=0;toss<number_of_toss/NUM;toss++){
        ranx=rand_r(&seed);
        rany=rand_r(&seed);
        //printf("%d %d \n",ranx,rany);
        x=((double)ranx/(double)RAND_MAX);
        y=((double)rany/(double)RAND_MAX);
        x=-1+2*x;
        y=-1+2*y;
        dist=x*x+y*y;
        if(dist<1){
            threadresult[thread]++;
        } 
    }
    

}

int main(int argc,char *argv[]){
    srand(time(NULL));
    int start,end;
    double pi_est;
    double x;
    double y;
    double dist;
    void *status;
    int total=0; 
    int rc;
    int i=0;
    int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    fp=fopen("log.txt","w");
    threadresult=(int *)malloc(NUM*sizeof(int));
    pthread_t *threads=(pthread_t *)malloc(NUM*sizeof(pthread_t));
    //pthread_mutex_init(&mutex,NULL);
    printf("number of core: %d\n",numCPU);
    printf("number of thread: %d\n",NUM);
    if(argc==2)
        number_of_toss=atoi(argv[1]);
    for(i=0;i<NUM;i++){
        rc=pthread_create(&threads[i],NULL,func,(void *)i);
        if(rc!=0)
            printf("we cant create thread %d\n",i);
    }
     
    for(i=0;i<NUM;i++)
        pthread_join(threads[i],NULL);
    for(i=0;i<NUM;i++)
    	number_in_circle+=threadresult[i];
    pi_est=(double)(4*number_in_circle)/((double)number_of_toss);
    printf("pi = %lf\n",pi_est); 
    


}
