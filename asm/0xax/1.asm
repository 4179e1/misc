section .data
    ; 0ah for new line (\n) 
    msg db "hello, world!", 0ah

section .text
    global _start
_start:
    ; syscall number, 1 is sys_write
    ;   size_t sys_write(unsigned int fd, const char * buf, size_t count);
    ; see https://github.com/torvalds/linux/blob/master/arch/x86/entry/syscalls/syscall_64.tbl
    mov     rax, 1
    mov     rdi, 1      ; 1st arg, fd, 1 for stdout
    mov     rsi, msg    ; 2nd arg, poniter to buf
    mov     rdx, 14     ; 3nd arg, count
    syscall
    mov     rax, 60     ; sys_exit
    mov     rdi, 0
    syscall