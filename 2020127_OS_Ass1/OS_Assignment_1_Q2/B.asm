section .bss
    val resb 8

section .data
    text db "I am in function B",10

section .text 
    extern c
    global b

b:
    call print
    lea r10, [rel c]
    push r10
    ret

print:
    mov [val],rdi
    mov rax,1
    mov rdi,1
    mov rsi,val
    mov rdx,16
    syscall
    ret