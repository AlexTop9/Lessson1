#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    // �������� ���������� � ������� ����������
    double cpu_freq = 0.0;
    FILE* cpuinfo = fopen("/proc/cpuinfo", "r"); // ��������� ���� � ����� � cpu ��� ������
    char line[256];
    while (fgets(line, sizeof(line), cpuinfo)) { // ��������� ������ ������ � line[]
        if (sscanf(line, "CPU MHz	: %lf", &cpu_freq) == 1)
            break;
    }
    fclose(cpuinfo); // ��������� ����

    printf("CPU FREQ: %.9lf Gz\n", cpu_freq / 1000.0); // ������� ������� ����������

    // ����� ���������� �� ������ ���������
    printf("Author: Alexander Ivanishev, KE-217\n"); 

    // ������������ ������ �� ����� ������, ������ ������� ����������
    usleep((useconds_t)(1000000.0 / cpu_freq));

    // �������� ��������� ��������
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // ���� ��� ����� ����������� ������ � �������� ��������
        double sum = 0.0;
        int i = 1;
        while (1) {
            sum += 1.0 / i * (i % 2 == 0 ? -1 : 1);
            printf("summa: %.9lf\n", sum);
            usleep(100000);
            i++;
        }
        // ��������� ���������� ��������� ��������
        exit(EXIT_SUCCESS);
    }
    else {
        // ���� ��� ����� ����������� ������ � ������������ ��������
        // �������� ���������� ��������� ��������
        wait(NULL);

        printf("ID of Parent process: %d\n", getpid());
        printf("ID of Child process: %d\n", pid);
    } 

    return 0;
}