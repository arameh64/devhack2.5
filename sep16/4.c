#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define N 5

int arr[N] = {1, 2, 3, 4, 5};

void print_arr(void)
{
	int i;

	printf("  arr: ");
	for (i = 0; i < N; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void handler(int sig)
{
	int i, tmp, sum;

	if (sig == SIGUSR1) {
		for (i = 0; i < N; i++)
			arr[i]++;
		puts("[SIGUSR1] +1");
		print_arr();
	} else if (sig == SIGUSR2) {
		for (i = 0; i < N / 2; i++) {
			tmp = arr[i];
			arr[i] = arr[N - 1 - i];
			arr[N - 1 - i] = tmp;
		}
		puts("[SIGUSR2] reverse");
		print_arr();
	} else if (sig == SIGINT) {
		sum = 0;
		for (i = 0; i < N; i++)
			sum += arr[i];
		puts("[SIGINT] state");
		print_arr();
		printf("  sum: %d\n", sum);
	} else if (sig == SIGTSTP) {
		for (i = 0; i < N; i++)
			arr[i] = 0;
		puts("[SIGTSTP] reset");
		print_arr();
	}
}

int main(void)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);

	printf("pid: %d\n", getpid());
	print_arr();

	while (1)
		pause();

	return 0;
}