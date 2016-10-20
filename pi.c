#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<time.h>
#define NUM 2

static long long int number_of_toss;
int result[NUM];

void *func(void *i){
    srand(time(NULL));
    int number_in_circle=0;
    int thread=(int)i;
    double dist;
    double x,y;
    for(int toss=0;toss<number_of_toss/NUM;toss++){
        x=((float)rand())/(float)RAND_MAX;
        y=((float)rand())/(float)RAND_MAX;
        x=-1+2*x;
        y=-1+2*y;
        dist=x*x+y*y;
        printf("thread %d exe %d\n",thread,toss);
        if(dist<1)
            number_in_circle++;        
    }
    result[thread]=number_in_circle;
    
    

}

int main(int argc,char *argv[]){
    
    int start,end;
    long long int number_in_circle=0;
    double pi_est;
    double x;
    double y;
    double dist;
    void *status;
    int total=0; 
    int rc;
    pthread_t threads[NUM];
    start=clock();
    if(argc==2)
        number_of_toss=atoi(argv[1]);
    for(int i=0;i<NUM;i++){
        rc=pthread_create(&threads[i],NULL,func,(void *)i);
        if(rc!=0)
            printf("we cant create thread %d\n",i);
    }
     
    for(int i=0;i<NUM;i++)
        pthread_join(threads[i],NULL);
    end=clock();
    for(int i=0;i<NUM;i++)
        total+=result[i];
    pi_est=4*total/((double)number_of_toss);
    //end=clock();
    printf("execute time %d\n",end-start);
    printf("pi = %lf\n",pi_est); 
    
    


}
