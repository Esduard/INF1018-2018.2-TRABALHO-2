.data

.text 
.globl foo

bee:

	movl $128, %eax
	leave
	ret

add:

	movl $100, %eax
	leave
	ret

foo:

	movl %edi, -0x18(%rbp)

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

	movl -0x18(%rbp), %edi

	leave
	ret
