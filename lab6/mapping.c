#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(){

    int mapFileFd,filefd;
    char *addr,*fileMem,buff[1];
    struct stat fileStats;
    int count;
    char file_name[100];
    int i=0;

    if((mapFileFd=open("memory.txt",O_RDWR)) < 0){
        fprintf(stderr,"Blad przy otwieraniu pliku do mapowania pamieci \n");
        return -1;
    }
    count=lseek(mapFileFd,0,SEEK_END);

    addr=mmap(NULL,count, PROT_WRITE , MAP_SHARED, mapFileFd, 0);

    if (addr == MAP_FAILED){
        fprintf(stderr,"Blad przy mapowaniu 1.  \n");
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
        
        addr=mmap(NULL,fileStats.st_size, PROT_WRITE | PROT_READ , MAP_SHARED, mapFileFd, 0);


        ftruncate(mapFileFd,fileStats.st_size);
        
        if (addr == MAP_FAILED){
            fprintf(stderr,"Blad przy mapowaniu 2.  \n");
            return -1;
        }

        while((count=read(filefd,buff,1))>0){
            addr[i++]=buff;
        }
    }


}
