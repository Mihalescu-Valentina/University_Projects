#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
        char* s;
        s=(char*)malloc(sizeof(char)*100);
        int p2a[2], a2p[2], a2b[2], i=0;
        size_t size=50;
        pipe(p2a); pipe(a2p); pipe(a2b);
        int v[11]={0};

        if(fork() == 0) // A
        {
                close(a2p[0]);close(p2a[1]);close(a2b[0]);


                        read(p2a[0], &s, sizeof(char) * 100);
                        close(p2a[0]);
                        for(i=0; i<strlen(s); i++)
                                if(isdigit(s[i]))
                                {
                                  int digit = s[i] - '0';
                                        v[digit]++;
                                }
                                else
                                        v[10]++;

                        write(a2p[1], &v, sizeof(v));
                        write(a2b[1], &v, sizeof(v));

                close(a2p[1]);close(a2b[1]);
                exit(0);
        }

        if(fork() == 0) //B
        {
                close(a2p[0]);close(a2p[1]);close(a2b[1]);close(p2a[0]);close(p2a[1]);
                read(a2b[0], &v, sizeof(v));
                close(a2b[0]);
                        int s = 0;
                        for(i=0; i<11; i++) s += v[i];
                        printf("B: %d\n", s);
          exit(0);
        }


        close(a2p[1]);close(p2a[0]);close(a2b[0]);close(a2b[1]);
        getdelim(&s,&size,'X',stdin);
        s[strlen(s)-1]='\0';
        printf("%s",s);

                //close(a2p[1]);close(p2a[0]);close(a2b[0]);close(a2b[1]);

                write(p2a[1], &s, strlen(s) + 1);
                close(p2a[1]);
                read(a2p[0], &v, sizeof(v));
                close(a2p[0]);
                for(i=0; i<11; i++)
                        printf("%d\n", v[i]);



        wait(0);wait(0);
        free(s);
        return 0;
}
