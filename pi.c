#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    
    long long int number_in_circle=0;
    srand(time(NULL));
    double x;
    double y;

    x=-1+2*x;
    y=-1+2*y;
    for(int toss=0;toss<number_of_toss;toss++){
        x=((float)rand())/(float)RAND_MAX;
        y=((float)rand())/(float)RAND_MAX;
        x=-1+2*x;
        y=-1+2*y;
            

    }
    


}
