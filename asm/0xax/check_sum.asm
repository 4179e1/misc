section .data
    ; equ for define constants
    num1: equ 100
    num2: equ 50
    msg: db "Sum is correct", 0ah

section .text
    global _start

; entry point
_start:
    mov rax, num1
    mov rbx, num2
    add rax, rbx ; rax += rbx
    cmp rax, 150
    jne .exit
    jmp .rightSum

.rightSum:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg
    mov rdx, 15
    syscall
    jmp .exit

.exit:
    mov rax, 60
    mov rdi, 0
    syscall