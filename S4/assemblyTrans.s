mp:
  subl $8, %esp
  movl 16(%esp), %edx
  movl 12(%esp), %ecx
  movl %ecx,%eax
  addl %ecx,%ecx
  addl %eax,%ecx
  cmpl %edx,%ecx
  jle m1
  movl %edx, %eax
  addl $8, %esp
  ret
 m1:
  movl %ecx, %eax
  addl $8, %esp
  ret


f:
  subl $8, %esp
  movl 20(%esp), %edx
  movl 16(%esp), %ecx
  movl 12(%esp), %ebx
  addl %ebx, %ecx
  cmpl %edx, %ecx
  jle m31
  movl %edx, %eax
  addl $8, %esp
  ret
m31:
  movl %ecx, %eax
  addl $8, %esp
  ret



fct:
    movl 4(%esp), %eax
    cmpl $0,%eax
    jg n
    movl $-1,%eax
    ret
n:  movl $0,%ebx
    movl %eax, %ecx
    movl $0, %eax
    movl $0, %edx
l:  addl $2, %ebx
    addl %ebx, %eax
    addl $1, %edx
    cmpl %ecx, %edx
    jl l
    ret