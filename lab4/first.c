#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <ucontext.h>

struct timespec ts;

void firstReaction(int sig, siginfo_t *sip, ucontext_t *uap)
{
	if(sig==SIGUSR1){
		printf("Wyslano do mnie sygnal: %d. Zamykam sie. \n ", sig);
		exit(0);
	}
}

int main()
{
	/*
	sigset_t sigset;
	sigemptyset(&sigset) ;
	sigaddset(&sigset, SIGHUP);
	sigprocmask(SIGINT,&sigset,NULL);
	*/


	struct sigaction action;
	action.sa_handler=(void*)firstReaction;  // przypisanie handlera
	action.sa_flags = SA_SIGINFO;		

	sigaction(SIGTERM, &action, 0);	
	sigaction(SIGUSR1, &action, 0);	
	sigaction(SIGUSR2, &action, 0);	
	sigaction(SIGALRM, &action, 0);	
	
	

	ts.tv_nsec = 100 * 1000000L;
	ts.tv_sec = 0;

	int i = 0;
	while (1)
	{
		i++;
		nanosleep(&ts, (struct timespec *)NULL);
	}
}

/*
       If SA_SIGINFO is specified in sa_flags, then sa_sigaction (instead of
       sa_handler) specifies the signal-handling function for signum.  This
       function receives three arguments, as described below.

       sa_mask specifies a mask of signals which should be blocked (i.e.,
       added to the signal mask of the thread in which the signal handler is
       invoked) during execution of the signal handler.  In addition, the
       signal which triggered the handler will be blocked, unless the
       SA_NODEFER flag is used.

	int sigaction(int signum, const struct sigaction *act,struct sigaction *oldact);
	int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);

	signum specifies the signal and can be any valid signal except
    SIGKILL and SIGSTOP.

	po ustawieniu sigprocmask nic nie przechodzi

*/
