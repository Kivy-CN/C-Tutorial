section .data
    num1 db '10', 0
    num2 db '20', 0
    result db 0, 0, 0 ; Initialize result to 0
    plus db '+', 0
    equals db '=', 0
    newline db 0xA

section .text
    global _start

_start:
    ; print num1
    mov eax, 4
    mov ebx, 1
    mov ecx, num1
    mov edx, 2
    int 0x80

    ; print plus
    mov eax, 4
    mov ebx, 1
    mov ecx, plus
    mov edx, 1
    int 0x80

    ; print num2
    mov eax, 4
    mov ebx, 1
    mov ecx, num2
    mov edx, 2
    int 0x80

    ; print equals
    mov eax, 4
    mov ebx, 1
    mov ecx, equals
    mov edx, 1
    int 0x80

    ; calculate result
    mov eax, [num1]
    sub eax, '0' ; convert ASCII digit to integer
    mov ebx, [num2]
    sub ebx, '0' ; convert ASCII digit to integer
    add eax, ebx
    add eax, '0' ; convert integer to ASCII digit
    mov [result], eax
    add result, '0' ; convert integer to ASCII digit

    ; print result
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, 1
    int 0x80
    
    ; print newline
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

    ; exit
    mov eax, 1
    xor ebx, ebx
    int 0x80