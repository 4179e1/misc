; sum 2 numbers
section .data
    SYS_WRITE equ 1
    STD_IN    equ 1
    SYS_EXIT  equ 60
    EXIT_CODE equ 0

    NEW_LINE db 0xa
    WRONG_ARGC db "Must be two command line arguments", 0xa

section .text
    global _start

; argument passing
; rdi - first argument
; rsi - second argument
; rdx - third argument
; rcx - fourth argument
; r8 - fifth argument
; r9 - sixth
; 7th on ward - passed in stack

; _start
_start:
    ; stack right after running 
    ; ...
    ; [rsp+16]  argv[1]
    ; [rsp+8]   argv[0]
    ; [rsp] argc
    ;
    ; pop: get the value in rsp, and rsp+=8
    ; push: rsp -=8, and store the value

    pop rcx ; get argc
    cmp rcx, 3
    jne argcError

    add rsp, 8          ; skip over argv[0]

    pop rsi             ; get argv[1]
    call str_to_int     ; return val in rax
    mov r10, rax       

    pop rsi             ; get argv[2]
    call str_to_int
    mov r11, rax

    add r10, r11

    mov rax, r10
    xor r12, r12        ; clear r12, it's a counter
    jmp int_to_str

; argError
argcError: 
    mov rax, 1
    mov rdi, 1
    mov rsi, WRONG_ARGC
    mov rdx, 35
    syscall
    jmp exit

; str_to_int
str_to_int:
    ; 1th arg in rsi
    xor rax, rax
    mov rcx, 10
next:
    cmp [rsi], byte 0 ; is it '\0'?
    je return_str

    mov bl, [rsi]
    sub bl, 48      ; ASCII code of '0' is 48
    mul rcx         ; rax *= rcx
    add rax, rbx
    inc rsi         ; get next char
    jmp next
return_str:
    ret


; int_to_str
int_to_str:
    mov rdx, 0
    mov rbx, 10

    ; Unsigned divide RDX:RAX by r/m64, with
    ; result stored in RAX := Quotient, RDX := Remainder.
    div rbx
    add rdx, 48   ; e.g. 3 + 48 = '3' 
    add rdx, 0x0  ; WTF?
    push rdx
    inc r12
    cmp rax, 0x0
    jne int_to_str
    jmp print

print:
    ; calculate number length
    mov rax, 1
    mul r12
    mov r12, 8
    ; Unsigned multiply (RDX:RAX := RAX ∗ r/m64).
    mul r12
    mov rdx, rax  ; 3rd parameter for sys_write

    ; print sum
    mov rax, SYS_WRITE
    mov rdi, STD_IN
    mov rsi, rsp
    syscall

    jmp exit

exit:
    mov rax, SYS_EXIT
    mov rdi, EXIT_CODE
    syscall
