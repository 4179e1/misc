section .data

count	equ		05
data	db		125, 235, 197, 91, 48
sum		dw		0000

section .text
	global _start

_start:
		mov		ecx, count
		mov		esi, offset data
		mov		ax, 00
back:
		add		al, [si]
		jnc		over
		inc		ah
over:
		inc		esi
		dec		ecx
		jnz		back
;		mov		sum, eax

		mov		eax, 1
		mov		ebx, 0
		int 	80h
