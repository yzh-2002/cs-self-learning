#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    int pid;
    int p[2]; //0=> read 1->write
    pipe(p);

    if (fork() == 0){
        char buf[16];
        // child => receive->send
        pid =getpid();
        if (read(p[0],buf,15) == -1){
            fprintf(2,"Child receive message failed!!");
            exit(1);
        }
        close(p[0]); //Warning: remember close unuse fd
        printf("%d: received ping\n",pid);
        if (write(p[1],buf,sizeof(buf)) == -1){
            fprintf(2,"Child send message failed!!");
            exit(1);
        }
        close(p[1]);
        exit(0);
    }else{
        // father => send->receive
        char buf[15];
        pid =getpid();
        if (write(p[1],"Hello World!!",13) == -1){
            fprintf(2,"Father send message failed!!");
            exit(1);
        }
        close(p[1]);
        wait(0); 
        if (read(p[0],buf,15) == -1){
            fprintf(2,"Father receive message failed!!");
            exit(1);
        }
        printf("%d: received pong\n",pid);
        close(p[0]);
        exit(0);
    }
}