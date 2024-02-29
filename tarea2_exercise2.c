#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void process(char id, int duracion) {
	printf("Proceso %c durmiendo por %d segundos...\n", id, duracion);
	sleep(duracion);
	printf("Proceso %c ha terminado de dormir \n", id);
	wait(NULL);
}

char getChar(int i) {
    return (char)(i + 65);
}

int main() {
	int N = 3;
	for (int i = 0; i < N; i++) {
		int pid = fork();
		if (pid != 0) {
			process(getChar(i), ((i+1)*5));
			if (i+1 < N) {
				printf("%c: he terminado de esperar a mi hijo %c \n", getChar(i), getChar(i+1));
			}
			break;
		}
	}
}