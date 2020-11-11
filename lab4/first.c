#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <ucontext.h>
#include <stdlib.h>

sigset_t sigset;
int flag=0;

void firstReaction(int sig, siginfo_t *sip, ucontext_t *uap)
{

	if(sig==SIGTERM){
		printf("Wyslano do mnie sygnal: %d. Zamykam sie.\n ", sig);
		exit(0);
	}

	if(sig==SIGUSR1){
		printf("Wyslano do mnie sygnal: %d. Wracam do pracy.\n ", sig);
	}

	if(sig==SIGUSR2){
		if(!flag){
			printf("Wyslano do mnie sygnal: %d. Teraz sygnal bedzie niewidoczny przez 10 sekund.\n ", sig);
		}else{
			printf("Oczekiwal sygnal w kolejce. Domyslnie ignoruje. \n");
			return;
		}
		flag=1;			// ustawia flage
	}

	if(sig==SIGALRM){}

}

int main()
{
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGUSR2);  // dodaje SIGUSR1 do setu
	
	struct sigaction action;
	action.sa_handler=(void*)firstReaction;  // przypisanie handlera
	action.sa_flags = SA_SIGINFO;		

	sigaction(SIGTERM, &action, 0);		// przypisanie akcji do sygnalow
	sigaction(SIGUSR1, &action, 0);	
	sigaction(SIGUSR2, &action, 0);	
	sigaction(SIGALRM, &action, 0);	
	
	struct timespec ts;
	ts.tv_nsec = 500000000L;
	ts.tv_sec = 0;

	int i = 0, loopCounter=0;

	while (1)
	{
		i++;
		nanosleep(&ts, (struct timespec *)NULL);
		if(flag){
			if(!loopCounter) sigprocmask(SIG_BLOCK,&sigset,NULL);	// blokuje sygnal
			loopCounter++;
			if(loopCounter>20){
				printf("Jestem juz widoczny ! \n");
				loopCounter=0;
				sigprocmask(SIG_UNBLOCK,&sigset,NULL);
				flag=!flag;
			}
		}
	}
}


