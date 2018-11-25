.data
.text 
.globl fun1,foo


fun1:
	push %rbp
	movq %rsp,%rbp
	subq $32,%rsp
	movl %edi,%r10d
	imul %edi,%r10d
	movl %r10d,-0x04(%rbp)
	movl -0x04(%rbp),%eax
	leave
	ret
foo:
	push %rbp
	movq %rsp,%rbp
	subq $32,%rsp
	cmpl $0,%edi
	jne fun2ne
	movl $0,%eax
	leave
	ret
fun2ne:
	movl %edi,%r10d
	subl $1,%r10d
	mov %r10d,-0x04(%rbp)
	mov %edi,-0x18(%rbp)
	call fun1
	movl %eax,-0x08(%rbp)
	movl -0x18(%rbp),%edi
	movl %edi,-0x18(%rbp)
	movl -0x04(%rbp),%edi
	call foo
	movl %eax,-0x04(%rbp)
	movl -0x18(%rbp),%edi
	movl -0x04(%rbp),%r10d
	addl -0x08(%rbp),%r10d
	mov %r10d,-0x04(%rbp)
	movl -0x04(%rbp),%eax
	leave
	ret
	