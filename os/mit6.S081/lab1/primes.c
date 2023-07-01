#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
/*
每一个子进程的执行都依赖于上一级进程的输入
*/
void print_primes(int *p)
{
    close(p[1]);
    int cp[2];
    pipe(cp);
    int prime, target;
    // 递归结束条件
    if (read(p[0], &prime, 4) == 0)
    {
        close(p[0]);
        close(cp[0]);
        close(cp[1]);
        exit(0);
    }
    else
    {
        printf("prime %d\n", prime); // first must be prime
    }
    if (fork() == 0)
    {
        print_primes(cp);
    }
    else
    {
        while (read(p[0], &target, 4) != 0)
        {
            // printf("target: %d\n", target);
            if (target % prime != 0)
            { // target不是prime倍数，传给子进程
                write(cp[1], &target, 4);
            }
        }
        close(p[0]);
        close(cp[1]);
        wait(0);
        exit(0);
    }
};

int main()
{
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        // child;
        print_primes(p);
    }
    else
    {
        close(p[0]);
        // father(generate process)
        for (int i = 2; i <= 35; i++)
        {
            write(p[1], &i, 4); // 指针类型
        }
        close(p[1]);
        wait(0); // 每一个父进程都在子进程结束后结束
        exit(0);
    }
    return 0;
};