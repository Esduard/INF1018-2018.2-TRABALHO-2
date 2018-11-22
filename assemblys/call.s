.data

.text 
.globl foo


foo:

	movl %edi, %r11d

	movl -0x04(%rsp), %edi
	movl -0x08(%rsp), %edi
	movl -0x0c(%rsp), %edi
	movl -0x10(%rsp), %edi
	movl -0x14(%rsp), %edi

	movl $1, %edi
	movl $100, %edi
	movl $1000,%edi

	movl $-1, %edi
	movl $-100, %edi
	movl $-1000,%edi
	
	call add

	movl %eax, -0x04(%rbp)
	movl %eax, -0x08(%rbp)
	movl %eax, -0x0c(%rbp)
	movl %eax, -0x10(%rbp)
	movl %eax, -0x14(%rbp)

	leave
	ret
