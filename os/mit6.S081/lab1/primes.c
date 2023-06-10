/**
 * reference: https://swtch.com/~rsc/thread/
*/
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void new_proc(int p[2]){
    int base;
    int primes;
    int flag;
    close(p[1]);
    //first number must be primes
    if (read(p[0],&base,4) !=4 ){
        fprintf(2,"Receive number failed!!");
        exit(1);
    } 
    printf("prime: %d\n",base);
    // unfiltered numbers exit or not?
    flag =read(p[0],&primes,4);
    if (flag){ //if there are still unfiltered numbers
        int newp[2];
        pipe(newp);
        if (fork()==0){
            new_proc(newp);
        }else{
            close(newp[0]);
            if (primes % base) write(newp[1], &primes, 4); //lazy to handle error boundary
            while (read(p[0],&primes,4)){
                 if (primes % base) write(newp[1], &primes, 4);
            }
            close(p[0]);
            close(newp[1]);
            wait(0);
            // exit(0); //Error
        }
    }
    exit(0);
};

int main(){
    int p[2];
    pipe(p);
    if (fork()==0){
        new_proc(p);
    }else{
        close(p[0]); //unuse
        for (int i=2;i<=35;i++){
            if (write(p[1],&i,4) != 4){
                fprintf(2,"Send number failed!!");
                exit(1);
            }
        }
        close(p[1]);
        wait(0);
        exit(0);
    }
    return 0;
}