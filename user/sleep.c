#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Invalid Input\n");
    }
    else{
        int len = strlen(argv[1]);
        int i;
        for(i = 0; i < len; i++){
            if(!(argv[1][i] >= '0' && argv[1][i] <= '9')){
                printf("Invalid Input\n");
                exit(0);
            }
        }
        int tim = atoi(argv[1]);
        sleep(tim);
    }
  exit(0);
}
