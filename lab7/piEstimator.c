#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define loopCount 10000
#define NUMOFTHREADS 100
#define R 1

void *printGreetingMess(void* value){
    float * average=(float *)value;
    time_t tt;
    float start = time(&tt);
    float randX=0; 
    float randY=0;
    float circleCount=0,squareCount=0;
    srand((unsigned int)time(NULL)); 

    for(int i=0;i<loopCount;i++){
        start = time(&tt);
        randX=((float)rand()/(float)(RAND_MAX)) * 2*R;  // losujemy w zakresie 0.0 : R.0
        randY=((float)rand()/(float)(RAND_MAX)) * 2*R; 
        
        squareCount++;
        if((randX-R)*(randX-R)+(randY-R)*(randY-R)<=R*R) // rownanie okregu - srodek to (R,R)
            circleCount++;
    }

    float pi=4*(circleCount/squareCount);
    *average+=pi;
    pthread_exit(NULL);
}

int main(){

    pthread_t threads[NUMOFTHREADS];
    float *average= malloc(sizeof(float));
    *average=0;

    for(int i=0;i<NUMOFTHREADS;i++){
        if(pthread_create(&threads[i],NULL,printGreetingMess,(void*) average)){
            fprintf(stderr,"Blad przy tworzeniu watku ID: %d",i);
            return -1;
        }
    }

    for(int i=0;i<NUMOFTHREADS;i++){
        pthread_join(threads[i],NULL);
    }
    

    printf("%f \n",*average/NUMOFTHREADS);
    
    pthread_exit(NULL);
}