.data
format: .string "%d\n"
error_str: .string "runtime error\n"
scanf_int: .string "%d"

.text
.globl printString
.globl printInt
.globl error
.globl readInt
.globl readString

printString:
  pushl %ebp
  movl %esp, %ebp
  pushl 8(%ebp)
  call printf
  leave
  ret

printInt:
  pushl %ebp
  movl %esp, %ebp
  pushl 8(%ebp)
  pushl $format
  call printf
  leave
  ret

error:
  pushl %ebp
  movl %esp, %ebp
  pushl $error_str
  call printString
  add $4, %esp
  movl $1, %eax
  movl $0, %ebx
  int $0x80

readString:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	movl	$120, -16(%ebp)
	movl	-16(%ebp), %eax
	subl	$12, %esp
	pushl	%eax
	call	malloc@PLT
	addl	$16, %esp
	movl	%eax, -20(%ebp)
	movl	stdin@GOT(%ebx), %eax
	movl	(%eax), %eax
	subl	$4, %esp
	pushl	%eax
	leal	-16(%ebp), %eax
	pushl	%eax
	leal	-20(%ebp), %eax
	pushl	%eax
	call	getline@PLT
	addl	$16, %esp
	movl	-20(%ebp), %eax
	movl	-12(%ebp), %edx
	xorl	%gs:20, %edx
	je	.L3
	call	__stack_chk_fail_local
.L3:
	movl	-4(%ebp), %ebx
	leave
	ret

readInt:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	subl	$8, %esp
	leal	-16(%ebp), %eax
	pushl	%eax
	pushl   $scanf_int
	call	__isoc99_scanf@PLT
	addl	$16, %esp
	nop
.L5:
	movl	stdin@GOT(%ebx), %eax
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	%eax
	call	fgetc@PLT
	addl	$16, %esp
	cmpl	$10, %eax
	jne	.L5
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %edx
	xorl	%gs:20, %edx
	je	.L7
	call	__stack_chk_fail_local
.L7:
	movl	-4(%ebp), %ebx
	leave
	ret
