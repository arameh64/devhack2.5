#include <stdio.h>
#include <signal.h>
#include <string.h>

int hits;

void handler(int sig)
{
	hits++;
	printf("  [handler] %s\n", sig == SIGINT ? "SIGINT" : "SIGTSTP");
}

void show_pending(void)
{
	sigset_t pend;

	sigpending(&pend);
	printf("  SIGINT  pending: %s\n", sigismember(&pend, SIGINT) ? "yes" : "no");
	printf("  SIGTSTP pending: %s\n", sigismember(&pend, SIGTSTP) ? "yes" : "no");
}

int main(void)
{
	struct sigaction sa;
	sigset_t mask;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);

	puts("[1] free mode");
	raise(SIGINT);
	raise(SIGTSTP);
	printf("  hits=%d\n", hits);

	puts("[2] SIG_BLOCK");
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGTSTP);
	sigprocmask(SIG_BLOCK, &mask, NULL);
	raise(SIGINT);
	raise(SIGINT);
	raise(SIGINT);
	raise(SIGTSTP);
	printf("  hits=%d (blocked)\n", hits);

	puts("[3] sigpending");
	show_pending();

	puts("[4] SIG_UNBLOCK");
	sigprocmask(SIG_UNBLOCK, &mask, NULL);
	printf("  hits=%d\n", hits);
	show_pending();

	return 0;
}