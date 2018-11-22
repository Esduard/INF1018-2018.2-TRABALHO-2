.data

.text 
.globl foo

foo: 
	push   %rbp          	
	mov    %rsp,%rbp
   sub    $0x20,%rsp
   
   movl $10, %eax

   leave
   ret

   	