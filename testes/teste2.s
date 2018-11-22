.data

.text 
.globl foo

foo: 
	push   %rbp          	
	mov    %rsp,%rbp
   	sub    $0x20,%rsp
   
   	movl %edi, %r10d

   	addl $1, %r10d 

   	movl %r10d, -0x04(%rbp)

   	movl -0x04(%rbp), %eax

   	leave
   	ret

   	