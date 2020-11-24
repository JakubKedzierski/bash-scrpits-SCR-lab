#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

int main(){
    const char uiQuestion[]="\nPodaj nazwe pliku z obrazkiem: \n";
    char file_name[30];
    char buf[200];
    int count,pipefd[2],filefd,flag;

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
        
        close(0);
        dup(pipefd[0]); 

        execlp("display", "display", "-", NULL);        
        
        close(pipefd[0]);

    }else{
        close(pipefd[0]); // aby rodzic nie byl czytajacy

        write(1,uiQuestion,sizeof(uiQuestion));
        scanf("%s", file_name);

        if((filefd=open(file_name,O_RDONLY)) < 0){
            fprintf(stderr,"Blad przy probie odczytu zdjecia\n");
            return -1;
        }

        while((flag=read(filefd,&buf,200))>0){
            if(write(pipefd[1],&buf,flag)<0){
                fprintf(stderr,"Blad przy pisaniu do potoku\n");  
            }
        }
        close(filefd);
        close(pipefd[1]);
    }

}

