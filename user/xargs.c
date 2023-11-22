#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Invalid Input\n");
        exit(0);
    }
    char *opt;
    opt = malloc(strlen(argv[1]) + 1);
    memmove(opt, argv[1], strlen(argv[1]));
    opt[strlen(argv[1])] = 0;

    char *argu[MAXARG];

    int i;
    for(i = 1; i < argc; i++){
        argu[i - 1] = malloc(strlen(argv[i]) + 1);
        memmove(argu[i - 1], argv[i], strlen(argv[i]));
        argu[i - 1][strlen(argv[i])] = 0;
    }
    int now = argc - 1;
    argu[now + 1] = 0;
    int capacity = 512;
    argu[now] = malloc(capacity);
    char *ptr = argu[now];
    char readChar;
    while(read(0, &readChar, 1)){
        if(readChar != '\n'){
            *ptr = readChar;
            ptr++;
        }
        else{
            *ptr = 0;
            if(fork() == 0) exec(opt, argu);
            else wait(0);
            ptr = argu[now];
        }
    }
    for(i = 0; i <= argc - 1; i++) free(argu[i]);
    exit(0);
}
