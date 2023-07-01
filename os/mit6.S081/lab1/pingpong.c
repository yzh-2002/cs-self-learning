#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    int p[2];
    pipe(p);
    int fid,cid;
    char cbuf[2],fbuf[2];
    if (fork()==0){
        // child
        cid =getpid();
        read(p[0],cbuf,1); //block
        close(p[0]);
        printf("%d: received ping\n",cid);
        write(p[1],cbuf,1);
        close(p[1]);
        exit(0);
    }else{
        // father
        fid =getpid();
        write(p[1],"y",1);
        wait(0); //等待子进程的写入，不然会自读自写
        read(p[0],fbuf,1); 
        printf("%d: received pong\n",fid);
        close(p[0]);
        close(p[1]);
        exit(0);
    }
}