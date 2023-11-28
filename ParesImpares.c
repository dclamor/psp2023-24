
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <openssl/evp.h>
#include <asm-generic/signal.h>

#define N_ALEATORIOS 20
#define READ 0
#define WRITE 1

/*Crea un proceso que cree dos procesos hijos, luego generará N (20) números aleatorios.
Enviará los pares al primer hijo, los impares al segundo. Los hijos escribirán por pantalla
"Soy el hijo 1|2, he recibido ". Por cada número que mande el padre.*/
void pares_handler(int signal)
{
    #!/usr/local/bin/tcc -run
    if (signal == SIGUSR1)
    {
        printf("Señal hijo1 recibida\n");
    }
    else if (signal == SIGUSR2)
    {
        printf("Señal hijo2 recibida\n");
    }
}

int main(int argc, char *argv[])
{
    pid_t hijoPares;
    pid_t hijoImpares;
    int sumaPares;
    int sumaImpares;
    int pipePares[2];
    int pipeImpares[2];
    // Semilla para la generación de números aleatorios
    srand(time(NULL));

    if (pipe(pipeImpares) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipePares) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    hijoPares = fork();

    if (hijoPares == 0)
    {
        close(pipeImpares[READ]);
        close(pipeImpares[WRITE]);
        int num;
        int suma = 0;

        while ((read(pipePares[READ], &num, sizeof(num))) > 0)
        {
            printf("Soy el hijo 1 y he recibid %d", num);
            suma += num;
        }
        write(pipePares[WRITE], &suma, sizeof(suma));
        kill(getppid(), SIGUSR1);
        close(pipePares[READ]);
        close(pipePares[WRITE]);
        exit(0);
    }
    else
    {
        hijoImpares == fork();

        if (hijoImpares = 0)
        {
            close(pipePares[READ]);
            close(pipePares[WRITE]);
            int num;
            int suma = 0;

            while ((read(pipeImpares[READ], &num, sizeof(num))) > 0)
            {
                printf("Soy el hijo 1 y he recibid %d", num);
                suma += num;
            }
            write(pipeImpares[WRITE], &suma, sizeof(suma));
            kill(getppid(), SIGUSR2);
            close(pipeImpares[READ]);
            close(pipeImpares[WRITE]);
            exit(0);
        }
        for (int i = 0; i < N_ALEATORIOS; i++)
        {
            int numAleatorio = rand();
            if (numAleatorio % 2 == 0)
            {
                write(pipePares[WRITE], &numAleatorio, sizeof(numAleatorio));
            }
            else
            {
                write(pipeImpares[WRITE], &numAleatorio, sizeof(numAleatorio));
            }
        }
        close(pipeImpares[WRITE]);
        close(pipePares[WRITE]);
    
    wait(NULL);
    wait(NULL);
    
    sigwaitinfo((sigset_t[]){SIGUSR1}, NULL);
    read(pipePares[READ], &sumaImpares, sizeof(sumaPares));
    sigwaitinfo((sigset_t[]){SIGUSR1}, NULL);
    read(pipeImpares[READ], &sumaImpares, sizeof(sumaImpares));
    close(pipeImpares[READ]);
    close(pipePares[READ]);
    printf("La suma de pares es de %d y la de impares de %d", sumaPares, sumaImpares);
    }
    return 0;
}

/*El código que has proporcionado tiene varios problemas que necesitan ser corregidos :

    Hay un error de lógica al asignar valores a las variables hijoPares y hijoImpares.En lugar de verificar si son iguales a cero(== 0),
    estás asignando valores(= 0).Esto podría provocar problemas ya que se está asignando un valor entero a estas variables en lugar de realizar una comparación.
    La comparación correcta sería == 0 para verificar si el proceso actual es el hijo.                                                                                                                                                                                              El código que sigue después de la llamada a fork() no está dentro de una estructura if que compruebe si el proceso actual es el padre o el hijo.Es importante dividir el código para que cada proceso(padre e hijos) realice las tareas deseadas.
    La llamada a sigwaitinfo() y las operaciones de lectura y escritura en las tuberías(pipes)
    no se ejecutan debido a la presencia de un return 0;
    antes de esas líneas.
    No hay verificación de errores después de las llamadas a
    fork()
    Es importante verificar si la creación de procesos(fork)
    tiene éxito o no.
    Aquí está una versión modificada del código con las correcciones mencionadas:
    #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define N_ALEATORIOS 20
#define READ 0
#define WRITE 1

void pares_handler(int signal) {
    if (signal == SIGUSR1) {
        printf("Señal hijo1 recibida\n");
    } else if (signal == SIGUSR2) {
        printf("Señal hijo2 recibida\n");
    }
}

int main(int argc, char *argv[]) {
    pid_t hijoPares, hijoImpares;
    int sumaPares = 0, sumaImpares = 0;
    int pipePares[2], pipeImpares[2];

    srand(time(NULL));

    if (pipe(pipeImpares) == -1 || pipe(pipePares) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    hijoPares = fork();

    if (hijoPares == 0) {
        close(pipeImpares[READ]);
        close(pipeImpares[WRITE]);

        int num;
        while (read(pipePares[READ], &num, sizeof(num)) > 0) {
            printf("Soy el hijo 1 y he recibido %d\n", num);
            sumaPares += num;
        }

        write(pipePares[WRITE], &sumaPares, sizeof(sumaPares));
        kill(getppid(), SIGUSR1);

        close(pipePares[READ]);
        close(pipePares[WRITE]);
        exit(0);
    }

    hijoImpares = fork();

    if (hijoImpares == 0) {
        close(pipePares[READ]);
        close(pipePares[WRITE]);

        int num;
        while (read(pipeImpares[READ], &num, sizeof(num)) > 0) {
            printf("Soy el hijo 2 y he recibido %d\n", num);
            sumaImpares += num;
        }

        write(pipeImpares[WRITE], &sumaImpares, sizeof(sumaImpares));
        kill(getppid(), SIGUSR2);

        close(pipeImpares[READ]);
        close(pipeImpares[WRITE]);
        exit(0);
    }

    for (int i = 0; i < N_ALEATORIOS; i++) {
        int numAleatorio = rand();
        if (numAleatorio % 2 == 0) {
            write(pipePares[WRITE], &numAleatorio, sizeof(numAleatorio));
        } else {
            write(pipeImpares[WRITE], &numAleatorio, sizeof(numAleatorio));
        }
    }

    close(pipeImpares[WRITE]);
    close(pipePares[WRITE]);

    wait(NULL);
    wait(NULL);

    read(pipePares[READ], &sumaPares, sizeof(sumaPares));
    read(pipeImpares[READ], &sumaImpares, sizeof(sumaImpares));

    close(pipeImpares[READ]);
    close(pipePares[READ]);

    printf("La suma de pares es: %d\n", sumaPares);
    printf("La suma de impares es: %d\n", sumaImpares);

    return 0;
}
*/