#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

int main(int argc,char *argv[]){
    if(argc<2){
        fprintf(stderr,"Zle wywolanie. Wywolanie programu w postaci %s [nazwa pliku tekst] \n \n",argv[0]);
        return -1;
    }

    char buf[200];
    int count,pipefd[2],filefd;

    if (pipe(pipefd) == -1) {
        fprintf(stderr,"Nie uruchomiono potoku \n");
        return -1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr,"Blad przy tworzeniu nowego procesu \n");
        return -1;
    }
    
    if(pid==0){
        close(pipefd[1]); // aby dziecko nie bylo piszace
        
        close(0);       // przekierowanie potoku na standardowe wejscie
        dup(pipefd[0]); 

        execlp("display", "display", "-", NULL);      
        
        close(pipefd[0]);

    }else{
        close(pipefd[0]); // aby rodzic nie byl czytajacy

        if((filefd=open(argv[1],O_RDONLY)) < 0){
            fprintf(stderr,"Blad przy probie odczytu zdjecia\n");
            return -1;
        }

        while((count=read(filefd,&buf,200))>0){
            if(write(pipefd[1],&buf,count)<0){
                fprintf(stderr,"Blad przy pisaniu do potoku\n");  
            }
        }

        close(filefd);
        close(pipefd[1]);
    }

}

