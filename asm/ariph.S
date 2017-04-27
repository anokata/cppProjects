.data
format: .ascii "%d\n"
.text
.global main
main:

movq $32, %r8
subq %r8, %rsi
movq $5, %rax
mulq %rsi
movq $9, %r8
divq %r8
movq %rax, %rsi

movq $2, %rsi
movq $3, %rdi
call pow


   mov  $format, %rdi
   mov  %RAX, %rsi
   mov  $0, %eax
   call printf
   retq

pow:
    movq $1, %rax
    cmpq $0, %rsi
    jz end
loop:    
    mulq %rdi
    decq %rsi
    jnz loop
end:
    retq
