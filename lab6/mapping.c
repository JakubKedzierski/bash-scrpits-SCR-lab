#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
    int filefd=0;
    char *addr;
    struct stat fileStats;
    int count;
    
    if((filefd=open("plik.txt",O_RDONLY)) < 0){
        fprintf(stderr,"Blad przy odczycie pliku \n");
        return -1;
    }
    
    if (fstat(filefd, &fileStats) == -1){
        fprintf(stderr,"Blad przy wyciaganiu statystyk.  \n");
        return -1;
    }  

    addr=mmap(NULL,fileStats.st_size, PROT_READ, MAP_PRIVATE, filefd, 0);
    
    if (addr == MAP_FAILED){
        fprintf(stderr,"Blad przy mapowaniu.  \n");
        return -1;
    }

    if((count=write(STDOUT_FILENO,addr,fileStats.st_size))<0){
        fprintf(stderr,"Blad przy wypiswaniu pamieci.  \n");
        return -1;
    }


}
