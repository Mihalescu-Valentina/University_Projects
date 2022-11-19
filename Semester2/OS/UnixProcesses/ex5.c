/* Create a C program that runs a bash command received as a command line argument and prints its execution time.
 *  * Ex:
 *   * ./exe grep -E -c "^[a-z]{4}[0-9]{4}" /etc/passwd
 *    */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {

        if (argc < 2) {
                printf("Please provide at least one argument.\n");
                exit(1);
        }

        int f = fork();
        if(-1 == f) {
                perror("Error on fork: ");
                exit(1);
        } else if (0 == f) {
                if( -1 == execvp(argv[1], argv + 1)) {
                        perror("Error running the given command: ");
                        exit(1);
                }
        } else {
                wait(0);
                printf("%s\n",argv[0]);
                printf("s-a facut\n");
        }
        return 0;
}
