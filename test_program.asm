section .data
    message db '1 + 2 = 3', 0

section .text
    global _start

_start:
    ; Add 1 and 2
    mov eax, 1
    add eax, 2

    ; Convert the result to ASCII characters
    add eax, '0'
    mov [result+2], al
    mov byte [result+1], '+'
    mov byte [result], '1'

    ; Print the result
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, 11
    int 0x80

    ; Exit the program
    mov eax, 1
    xor ebx, ebx
    int 0x80

section .data
    result db '      =      ', 0
