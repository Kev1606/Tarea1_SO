#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int i, status;
    pid_t pids[5];

    // Crear 5 procesos hijos
    for (i = 0; i < 5; i++) {
        pids[i] = fork();

        // Si el valor devuelto por fork() es 0, estamos en el proceso hijo
        if (pids[i] == 0) {
            // Proceso hijo
            while (1) {
                // Esperar a ser cancelado
                sleep(1);
            }
        }
    }

    // Enviar señales de cancelación a los hijos
    for (i = 0; i < 5; i++) {
        kill(pids[i], SIGKILL);
        printf("Proceso %d aniquilado. \n", pids[i]);
    }

    return 0;
}
