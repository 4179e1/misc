section .data
	hello     db	'Hello, world!',10	; Our dear string
	helloLen  equ	$ - hello		; Length of our dear string

section	.text
    global _start

_start:
	pop	ebx		; argc (argument count)
	pop	ebx		; argv[0] (argument 0, the program name)
	pop	ebx		; The first real arg, a filename

	mov	eax,8		; The syscall number for creat() (we already have the filename in ebx)
	mov	ecx,00644Q	; Read/write permissions in octal (rw_rw_rw_)
	int	80h		; Call the kernel
				; Now we have a file descriptor in eax

	test	eax,eax		; Lets make sure the file descriptor is valid
	js	skipWrite	; If the file descriptor has the sign flag
				;  (which means it's less than 0) there was an oops,
				;  so skip the writing. Otherwise call the filewrite "procedure"
	call	fileWrite

skipWrite:
	mov	ebx,eax		; If there was an error, save the errno in ebx
	mov	eax,1		; Put the exit syscall number in eax
	int	80h		; Bail out

; proc fileWrite - write a string to a file
fileWrite:
	mov	ebx,eax		; sys_creat returned file descriptor into eax, now move into ebx
	mov	eax,4		; sys_write
				; ebx is already set up
	mov	ecx,hello	; We are putting the ADDRESS of hello in ecx
	mov	edx,helloLen	; This is the VALUE of helloLen because it's a constant (defined with equ)
	int	80h

	mov	eax,6		; sys_close (ebx already contains file descriptor)
	int	80h
	ret
; endp fileWrite

