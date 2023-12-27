section .data
    num1 dd 10
    num2 dd 20

section .text
    global _start

_start:
    mov eax, [num1]
    add eax, [num2]
    mov [num1], eax
    mov eax, 1
    xor ebx, ebx
    int 0x80