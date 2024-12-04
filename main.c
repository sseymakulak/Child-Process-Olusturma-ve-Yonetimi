#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // fork() komutu ile child process olusturuyoruz
    pid = fork();

    if (pid < 0) {
        // fork basarisiz oldu
        perror("Fork basarisiz oldu");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process: Dosya icin cat komutu calisiyor...\n");

        // cat komutunu çalistiriyoruz
        execlp("cat", "cat", "Dosya.txt", NULL);

        // execlp basarisiz olursa
        perror("execlp basarisiz");
        exit(1);
    } else {
        // Parent process
        printf("Parent process: Child process'in tamamlanmasi bekleniyor...\n");

        // wait() komutu ile child process'in bitmesini bekliyoruz
        if (wait(&status) == -1) {
            perror("wait basarisiz");
            exit(1);
        }

        // Çikis durumu kontrol ediliyor
        if (WIFEXITED(status)) {
            printf("Parent process: Child process basariyla sonlandi, cikis kodu: %d\n", WEXITSTATUS(status));
        } else {
            printf("Parent process: Child process hatali sonlandi .\n");
        }
    }

    return 0;
}
