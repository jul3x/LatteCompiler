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

readInt:
  pushl %ebp
  movl %esp, %ebp
  subl $4, %esp
  leal -4(%ebp), %eax
  pushl %eax
  pushl $scanf_int
  call scanf
  movl -4(%ebp), %eax
  leave
  ret

readString:
  ret
