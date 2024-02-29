#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void processes(int level, int quantity) {
	if (level > 3) return;
	
	for (int i = 0; i < quantity; i++) {
		pid_t pid = fork();
		
		if (pid < 0) {
			perror("Error al crear el proceso");
			exit(EXIT_FAILURE);
		} else if (pid == 0){	
			printf("Nivel %d - PID: %d - PPID: %d\n", level, getpid(), getppid());
			
			processes(level + 1, 5);
			
			break;
		}
	}
}

int main() {
	printf("Abuelo (Nivel 0) - PID: %d - PPID: %d\n", getpid(), getppid());
	processes(1, 5);
	for (int i = 0; i < 5; i++) wait(NULL);
	return 0;
}
