#include <asm/unistd_64.h>
#include <sys/mman.h>
#include <time.h>

// int syscall6(in)
// {
//     asm volatile
//     (
//         "movl $1, %%eax\n\t"
//         "movl $1, %%edi\n\t"
//         "movq %1, %%rsi\n\t"
//         "movl %2, %%edx\n\t"
//         "syscall"
//         : "=a"(ret)
//         : "g"(hello), "g"(hello_size)
//         : "%rdi", "%rsi", "%rdx", "%r10", "%r8", "%r9"
//     );
// }

int syscall6(int n, int a0, int a1, int a2, int a3, int a4, int a5)
{
    int ret;

    asm volatile
    (
        "mov %5, %%r10\n"
        "mov %6, %%r8\n"
        "mov %7, %%r9\n"
        "syscall"
        : "=a"(ret)
        : "a"(n), "D"(a0), "S"(a1), "d"(a2), "g"(a3), "g"(a4), "g"(a5)
    );
    return ret;
}
int syscall1(int n, int a0)
{
    int ret;
    asm volatile (
        "syscall"
        : "=a"(ret)
        : "a"(n), "D"(a0)
    );
    return ret;
}

int syscall0(int n)
{
    int ret;
    asm volatile (
        "syscall"
        : "=a"(ret)
        : "a"(n)
    );
    return ret;
}

struct timespec tv = {.tv_sec=5};
void stackstress(int n)
{
    char tab[n/4];

    if (n<=0)
        return;

    syscall6(__NR_nanosleep, (int) &tv, 0, 0, 0, 0, 0);
    stackstress(3*n/4);
}

void _start(void)
{
    int b=syscall1(__NR_brk, 0);
    syscall1(__NR_brk, b+10);
    stackstress(16*1024*1024);
    syscall6(__NR_mmap, 0, 4096, PROT_READ, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    syscall0(__NR_pause);
    syscall1(__NR_exit, 0);
}
