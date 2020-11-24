#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#define packageSize 10

int main(int argc,char *argv[]){

    if(argc<2){
        fprintf(stderr,"Zle wywolanie. Wywolanie programu w postaci %s [nazwa pliku tekst] \n \n",argv[0]);
        return -1;
    }

    int pipefd[2],filefd,countWords;
    char buf[packageSize];

    if (pipe(pipefd) == -1) {
        fprintf(stderr,"Nie uruchomiono potoku \n");
        return -1;
    }

    pid_t pid = fork();

    if(pid <0){
        fprintf(stderr,"Blad przy tworzeniu nowego procesu \n");
        return -1;

    }else if(pid==0){  // dziecko
        close(pipefd[1]); // aby dziecko nie bylo piszace
        
        while((countWords=read(pipefd[0],buf,packageSize))>0){
            
            if((countWords=write(1,buf,countWords))<0){
                fprintf(stderr,"Blad przy przekazywaniu do potoku");
            }
        }

    }else{ // rodzic
        close(pipefd[0]); // aby rodzic nie byl czytajacy
        if((filefd=open(argv[1],O_RDONLY)) < 0){
            fprintf(stderr,"Blad przy odczycie pliku \n");
            return -1;
        } 
        while((countWords=read(filefd,buf,packageSize))>0){

            if((countWords=write(pipefd[1],buf,countWords))<0){
                fprintf(stderr,"Blad przy przekazywaniu do potoku");
            }

        }

    }
}