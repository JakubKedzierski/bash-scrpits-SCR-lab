#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define fifoPipe "potok1"
#define packageSize 10

/* Komenda odczytujaca tail -c +0 -f potok1 */
/* wczesniej utworzono w katalogu potok nazwany poprzez mknod potok1 p */

int main(int argc,char *argv[]){
    
    if(argc<2){
        fprintf(stderr,"Zle wywolanie. Wywolanie programu w postaci %s [nazwa pliku tekst] \n \n",argv[0]);
        return -1;
    }

    int pipeFd,filefd,countWords;
    char buf[200];

    int texts=argc;

    mode_t mask = umask(0);

    if((pipeFd=open(fifoPipe,O_WRONLY)) == -1){
        fprintf(stderr,"Blad przy otwieraniu potoku \n");
        return -1;
    }


    while(--texts>0){
        
        if((filefd=open(argv[texts],O_RDONLY)) < 0){
            fprintf(stderr,"Blad przy odczycie pliku \n");
            return -1;
        } 

        while((countWords=read(filefd,buf,packageSize))>0){

            if(write(pipeFd,buf,countWords)<0){
                fprintf(stderr,"Blad przy przekazywaniu do potoku");
            }

        }

        fprintf(stdout,"Czekam na kolejny plik");
        sleep(2);

        //feof(filefd); 
    }
    close(pipeFd);

}