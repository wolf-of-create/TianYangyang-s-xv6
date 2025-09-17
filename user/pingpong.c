// user/pingpong.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char **argv[])
{
    int pptc[2],pctp[2];
    pipe(pptc);
    pipe(pctp);
    if(fork()!=0)//parent
    {
        close(pptc[0]);
        char buf='x';
        write(pptc[1],&buf,1);
        close(pptc[1]);
        close(pctp[1]);
        read(pctp[0],&buf,1);
        printf("%d: received pong\n",getpid());
        wait(0);
    }else{
        close(pptc[1]);
        char buf;
        read(pptc[0],&buf,1);
        printf("%d: received ping\n",getpid());
        close(pctp[0]);
        write(pctp[1],&buf,1);
        close(pctp[1]);
    }
    close(pptc[0]);
    close(pctp[0]);
    exit(0);
}