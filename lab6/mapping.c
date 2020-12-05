#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
    int filefd=0,mapFileFd;
    char *addr;
    struct stat fileStats;
    int count;
    char file_name[100];

    if((mapFileFd=open("memory.txt",O_WRONLY)) < 0){
        fprintf(stderr,"Blad przy otwieraniu pliku do mapowania pamieci \n");
        return -1;
    }

    while(1){
        printf("Podaj nazwe pliku do odczytu \n");
        scanf("%s",file_name);

        if((filefd=open(file_name,O_RDONLY)) < 0){
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
        
        ftruncate(mapFileFd,fileStats.st_size);
        
        if((count=write(mapFileFd,addr,fileStats.st_size))<0){
            fprintf(stderr,"Blad przy wypiswaniu pamieci.  \n");
            return -1;
        }
    }


}
