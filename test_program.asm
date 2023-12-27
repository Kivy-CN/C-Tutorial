section .data
    a db 10
    b db 20
    result db 0
    output db "The result is: ", 0
    buffer db 0

section .text
    global _start

_start:
    ; 将变量a的值存入寄存器AL
    mov al, byte [a]
    
    ; 将变量b的值存入寄存器BL
    mov bl, byte [b]
    
    ; 将寄存器AL和BL相加，并将结果存入寄存器AL
    add al, bl
    
    ; 将寄存器AL的值存入变量result
    mov byte [result], al
    
    ; 将结果转换为字符形式并存储在缓冲区中
    mov ah, 0
    add al, '0'
    mov byte [buffer], al
    
    ; 打印输出结果前的字符串
    mov eax, 4
    mov ebx, 1
    mov ecx, output
    mov edx, 15
    int 0x80
    
    ; 打印输出结果
    mov eax, 4
    mov ebx, 1
    mov ecx, buffer
    mov edx, 2
    int 0x80
    
    ; 退出程序
    mov eax, 1
    xor ebx, ebx
    int 0x80
