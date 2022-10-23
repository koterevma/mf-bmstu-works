#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

double f(double x) {
    return sqrt(x);
}

double integral(double a, double b, double h) {
    double n = (b - a) / h;
    double s = h * (f(a) + f(b)) / 2.0;
    for(int i = 1; i <= n - 1; i++)
        s += h * f(a + h * i);

    return s;
}

int main(int argc, char* argv[]) {
    int   pipefd[2];
    char  buf[PIPE_BUF];

    pid_t cpid1;
    pid_t cpid2;

    double a = 0.;
    double b = 10.;
    double h = 0.0001;


    double result = 0.;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid1 = fork();
    if (cpid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid1 == 0) {    /* Child reads from pipe */
        close(pipefd[0]);  // Closing read end of pipe
        double b1 = (a + b) / 2.0;
        double rez1 = integral(a, b1, h);
        
        fprintf(stderr, "result in p1 = %f\n", rez1);

        sprintf(buf, "%f", rez1);

        write(pipefd[1], buf, PIPE_BUF);
        close(pipefd[1]);

        fprintf(stderr, "Child 1 done\n");
        exit(EXIT_SUCCESS);
    } else {
        cpid2 = fork();
        if (cpid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (cpid2 == 0) {
            close(pipefd[0]);  // Closing read end of pipe
            double a2 = (a + b) / 2.0; 

            double rez2 = integral(a2, b, h);

            fprintf(stderr, "result from p2 = %f\n", rez2);

            sprintf(buf, "%f", rez2);

            write(pipefd[1], buf, PIPE_BUF);
            close(pipefd[1]);

            fprintf(stderr, "Child 2 done\n");
            exit(EXIT_SUCCESS);
        } else { // Parent process
            close(pipefd[1]);  // Closing write end
            pid_t w;

            w = waitpid(cpid1, NULL, WUNTRACED);
            if (w == -1) {
                perror("waitpid 1");
                exit(EXIT_FAILURE);
            }

            w = waitpid(cpid2, NULL, WUNTRACED);
            if (w == -1) {
                perror("waitpid 2");
                exit(EXIT_FAILURE);
            }

            int n;
            double rez = 0.;
            while ((n = read(pipefd[0], buf, PIPE_BUF)) > 0) {
                fprintf(stderr, "Parent recieved from pipe: %s\n", buf);
                rez += atof(buf);
            }
            if (n == -1) {
                perror("Read from pipe");
                exit(EXIT_FAILURE);
            }

            printf("Result of child threads = %f\n", rez);

            printf("Result calculated only in parent thread = %f\n", integral(a, b, h));

            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}
