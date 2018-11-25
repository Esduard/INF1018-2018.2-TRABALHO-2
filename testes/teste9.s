.text

.globl fat

fat:
	push %rbp
	movq %rsp,%rbp
	subq $32,%rsp

	cmpl $0,%edi
	jne continue
	movl $0,%eax
	movq %rbp,%rsp
	pop %rbp
	ret

continue:
	movl %edi, %r10d
	subl $1, %r10d
	movl %r10d, -0x04(%rbp)

	movl %edi, -0x18(%rbp)
	movl -0x04(%rbp),%edi
	call fat
	movl -0x18(%rbp),%edi
	movl %eax,-0x08(%rbp)
	movl -0x04(%rbp),%r10d
	addl -0x08(%rbp),%r10d
	movl %r10d,-0x0c(%rbp)
	movl -0x0c(%rbp),%eax
	movq %rbp,%rsp
	pop %rbp
	ret

foo:
	
