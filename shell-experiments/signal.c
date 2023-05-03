#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void int_handler(int signum) {
	rl_done = 1;
	// rl_replace_line("", 0);
	// rl_redisplay();
}

int main(void) {
	rl_getc_function = getc;
	signal(SIGINT, int_handler);

	char *input = readline("hoi>");
	printf("Input was: %s\n", input);
	free(input);
	return (0);
}