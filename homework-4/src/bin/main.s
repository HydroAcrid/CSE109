.file	"main.c"
	.text
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$2, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	add@PLT
	movl	$4, %esi
	movl	$3, %edi
	movl	%eax, %ebx
	xorl	%eax, %eax
	call	sub@PLT
	addl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 10.3.0"
	.section	.note.GNU-stack,"",@progbits
