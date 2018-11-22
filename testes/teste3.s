.data

.text 
.globl foo

foo: 
	push   %rbp          	
	mov    %rsp,%rbp
    sub    $0x20,%rsp
   
   	cmpl $0, %edi
   	jne zret

      movl $1, %eax
      leave
      ret

zret: 

   	movl %edi, %r10d
   	addl $0, %r10d
   	movl %r10d, -0x04(%rbp)

   	movl -0x04(%rbp), %r10d
   	subl $1, %r10d
   	movl %r10d, -0x08(%rbp)

   	movl -0x04(%rbp), %r10d
   	imul -0x08(%rbp), %r10d
   	movl %r10d, -0x04(%rbp)

   	movl -0x04(%rbp), %eax

      leave
      ret

   	