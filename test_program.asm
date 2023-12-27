section .data
    result db "Result: %d", 0

section .text
    global _start

_start:
    ; 计算10 + 20
    mov eax, 10
    add eax, 20

    ; 将结果打印到终端命令行
    push eax
    push result
    call printf
    add esp, 8

    ; 退出程序
    mov eax, 1
    xor ebx, ebx
    int 0x80

section .data
    extern printf
