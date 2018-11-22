.data

.text 
.globl foo

foo: 
   	cmpl $0, %edi
   	
      cmpl $0,-0x04(%rbp)
      cmpl $0,-0x08(%rbp)
      cmpl $0,-0x0c(%rbp)
      cmpl $0,-0x10(%rbp)
      cmpl $0,-0x14(%rbp)

      movl $100, %r10d
   	cmpl $0,%r10d

      movl $1000, %r10d
      cmpl $0,%r10d

   	jne end 

      movl $1, %eax
      movl $100, %eax
      movl -0x04(%rbp),%eax
      movl -0x08(%rbp),%eax
      movl -0x0c(%rbp),%eax
      movl -0x10(%rbp),%eax
      movl -0x14(%rbp),%eax
      movl %edi, %eax



      leave
      ret


   	movl -0x04(%rbp), %eax
	

end:
   leave
   ret

   	