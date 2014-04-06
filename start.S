.globl _start

_start:
    call main
    mov %rax, %rdi
    mov $60, %rax   # __NR_exit /usr/include/asm/unistd_64.h
    syscall

_start_x86_32:
    movl $1, %eax
    int $0x80
