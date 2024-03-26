#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    // Получаем информацию о частоте процессора
    double cpu_freq = 0.0;
    FILE* cpuinfo = fopen("/proc/cpuinfo", "r"); // открываем файл с инфой о cpu для чтения
    char line[256];
    while (fgets(line, sizeof(line), cpuinfo)) { // считываем каждую строку в line[]
        if (sscanf(line, "CPU MHz	: %lf", &cpu_freq) == 1)
            break;
    }
    fclose(cpuinfo); // закрываем файл

    printf("CPU FREQ: %.9lf Gz\n", cpu_freq / 1000.0); // выводим частоту процессора

    // Вывод информации об авторе программы
    printf("Author: Alexander Ivanishev, KE-217\n"); 

    // Приостановка работы на число секунд, равное частоте процессора
    usleep((useconds_t)(1000000.0 / cpu_freq));

    // Создание дочернего процесса
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Этот код будет выполняться только в дочернем процессе
        double sum = 0.0;
        int i = 1;
        while (1) {
            sum += 1.0 / i * (i % 2 == 0 ? -1 : 1);
            printf("summa: %.9lf\n", sum);
            usleep(100000);
            i++;
        }
        // Завершаем выполнение дочернего процесса
        exit(EXIT_SUCCESS);
    }
    else {
        // Этот код будет выполняться только в родительском процессе
        // Ожидание завершения дочернего процесса
        wait(NULL);

        printf("ID of Parent process: %d\n", getpid());
        printf("ID of Child process: %d\n", pid);
    } 

    return 0;
}