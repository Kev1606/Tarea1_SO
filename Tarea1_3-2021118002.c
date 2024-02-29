#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int random_number(int seed) {
    srand(seed);
    return rand() % 100;
}

int main() {
    srand(time(NULL));

    int n = 5;
    int states[n];

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Error al crear el proceso hijo");
            exit(0);
        } else if (pid == 0) {
            // Código del proceso hijo
            int random = random_number(getpid());
            printf("Hijo %d - Número Aleatorio: %d\n", getpid(), random);
            exit(random);
        }
    }

    // Código del proceso padre
    for (int i = 0; i < n; i++) {
        wait(&states[i]);
    }

    // Imprimir los resultados del padre
    for (int i = 0; i < n; i++) {
        printf("Padre - Hijo %d retornó: %d\n", i + 1, WEXITSTATUS(states[i]));
    }

    return 0;
}
