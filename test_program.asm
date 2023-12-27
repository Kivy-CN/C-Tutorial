section .data
    message db '1 + 2 = ', 0     ; 定义消息内容，初始值为 '1 + 2 = '
    result db 0                 ; 定义结果变量，初始值为 0
    len equ $-message           ; 计算消息内容的长度

section .text
    global _start

_start:
    ; 设置方程式
    mov eax, 1                 ; 将 1 压入寄存器 eax
    add eax, 2                 ; 将 eax 的值与 2 相加
    mov byte [result], al      ; 将结果存储在 result 变量中

    ; 打印方程式
    mov edx, len              ; 将消息内容的长度存储在 edx 寄存器
    mov ecx, message          ; 将消息内容的地址存储在 ecx 寄存器
    mov ebx, 1                ; 将标准输出的文件描述符 1（stdout）存储在 ebx 寄存器
    mov eax, 4                ; 将系统调用号 4（写入）存储在 eax 寄存器
    int 0x80                  ; 发送系统调用

    ; 将结果转换为可打印字符
    add byte [result], '0'     ; 将结果变量的值加 48（字符 '0' 的ASCII码）

    ; 打印结果
    mov edx, 1                ; 将结果变量的长度存储在 edx 寄存器
    mov ecx, result           ; 将结果变量的地址存储在 ecx 寄存器
    mov ebx, 1                ; 将标准输出的文件描述符 1（stdout）存储在 ebx 寄存器
    mov eax, 4                ; 将系统调用号 4（写入）存储在 eax 寄存器
    int 0x80                  ; 发送系统调用

    ; 退出
    mov eax, 1                ; 将系统调用号 1（退出）存储在 eax 寄存器
    xor ebx, ebx              ; 将退出状态码清零
    int 0x80                  ; 发送系统调用