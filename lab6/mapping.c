#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

void handleCriticalError(const char* errorMessage){
    fprintf(stderr,"%s \n",errorMessage);
    fprintf(stderr, "Program konczy dzialanie \n \n ");
    exit -1;
}

int main(){
    int mapFileFd,filefd;
    char *addr,buff[1];
    struct stat fileStats;
    int count,letters;
    char file_name[100];
    int i=0;

    if((mapFileFd=open("memory.txt",O_RDWR)) < 0)
        handleCriticalError("Blad przy otwieraniu pliku do mapowania pamieci");

    while(1){
        count=lseek(mapFileFd,0,SEEK_END);

        printf("Podaj nazwe pliku do odczytu \n");
        scanf("%s",file_name);

        if((filefd=open(file_name,O_RDONLY)) < 0){
            handleCriticalError("Blad przy odczycie pliku. Prawdopodobnie zla nazwa \n");
        }
        
        if (fstat(filefd, &fileStats) == -1){
            handleCriticalError("Blad przy wyciaganiu statystyk");
        }  
        
        addr=mmap(NULL,fileStats.st_size+count, PROT_WRITE | PROT_READ , MAP_SHARED, mapFileFd, 0);

        ftruncate(mapFileFd,fileStats.st_size+count);
        
        if (addr == MAP_FAILED){
            handleCriticalError("Blad przy kolejnym mapowaniu");
        }

        i=0;
        while((letters=read(filefd,buff,1))>0){
            addr[count+i++]=buff[0];
        }
    }


}
