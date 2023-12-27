section .data
    result db "Result: %d", 0

section .text
    global _start

_start:
    ; 计算10 + 20
    mov eax, 10
    add eax, 20

    ; 将结果转换为字符串
    mov ebx, 10
    xor ecx, ecx
    mov edi, 10
    mov esi, result
    call itoa

    ; 将结果打印到终端命令行
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, 10
    int 0x80

    ; 退出程序
    mov eax, 1
    xor ebx, ebx
    int 0x80

section .data
    extern itoa
