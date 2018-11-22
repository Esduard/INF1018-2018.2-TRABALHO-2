.data

.text 
.globl foo


foo: 

	push %rbp
	movq %rsp, %rbp
	subq $32, %rsp

	movl -0x04(%rsp), %eax
	movl -0x08(%rsp), %eax
	movl -0x0c(%rsp), %eax
	movl -0x10(%rsp), %eax
	movl -0x14(%rsp), %eax
	
	movl $100, %eax

	leave
	ret




	

	
