#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM 5

void *printGreetingMess(void* ID){
    long id=(long) ID;
    printf("Hello SCR. Written by thread %ld \n",id);
    pthread_exit(NULL);
}

int main(){

    pthread_t threads[NUM];
    long id=0;
    for(int i=0;i<NUM;i++){
        id++;
        if(pthread_create(&threads[i],NULL,printGreetingMess,(void*) id)){
            fprintf(stderr,"Blad przy tworzeniu watku ID: %d",i);
            return -1;
        }
        if(pthread_join(threads[i],NULL)){
            fprintf(stderr,"Blad przy czekaniu, ID: %d",i);
            return -1;
        }
    }

    pthread_exit(NULL); 
}