#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void transfer(int left_pipe[2]){
    close(left_pipe[1]);
    int prime = 0;
    if(read(left_pipe[0], &prime, 4) == 0){
        close(left_pipe[0]);
        exit(0);
    }     
    int p[2];
    pipe(p);
    if(fork() == 0){
        transfer(p);
    }
    else{
        printf("prime %d\n", prime);
        int now = prime;
        while(read(left_pipe[0], &now, 4) != 0){
            if(now%prime != 0) write(p[1], &now, 4);
        }
        close(left_pipe[0]);
        close(p[1]);
        close(p[0]);
        wait(0);
        exit(0);
    }
}

int main(int argc, char *argv[]){
    int p[2];
    pipe(p);
    int i;
    int prime = 2;
    printf("prime %d\n", prime);
    if(fork() == 0){
        transfer(p);
    }
    else{
        for(i = 3; i <= 35; i++){
            if(i%prime != 0) write(p[1], &i, 4); 
        }
        close(p[1]);
        close(p[0]);
        wait(0);
    }
    exit(0);
}
