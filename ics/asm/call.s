	.file	"call.c"
	.text
	.p2align 4,,15
.globl _swap_add
	.def	_swap_add;	.scl	2;	.type	32;	.endef
_swap_add:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	pushl	%ebx
	movl	12(%ebp), %ebx
	movl	(%ecx), %eax
	movl	(%ebx), %edx
	movl	%edx, (%ecx)
	movl	%eax, (%ebx)
	addl	%edx, %eax
	popl	%ebx
	popl	%ebp
	ret
	.p2align 4,,15
.globl _caller
	.def	_caller;	.scl	2;	.type	32;	.endef
_caller:
	pushl	%ebp
	movl	%esp, %ebp
	leal	-4(%ebp), %eax
	subl	$16, %esp
	movl	%eax, 4(%esp)
	leal	-8(%ebp), %eax
	movl	$537, -8(%ebp)
	movl	$1057, -4(%ebp)
	movl	%eax, (%esp)
	call	_swap_add
	movl	-8(%ebp), %edx
	movl	-4(%ebp), %ecx
	leave
	subl	%ecx, %edx
	imull	%edx, %eax
	ret
