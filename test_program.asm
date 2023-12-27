section .data
    // 定义变量num1，类型为双字，值为10
    num1 dd 10
    // 定义变量num2，类型为双字，值为20
    num2 dd 20

section .text
    // 定义全局变量_start
    global _start

_start:
    // 将num1的值赋给eax
    mov eax, [num1]
    // 将num2的值加到eax上
    add eax, [num2]
    // 将eax的值赋给num1
    mov [num1], eax
    // 将eax的值赋为1
    mov eax, 1
    // 将ebx的值赋为0
    xor ebx, ebx
    // 调用int 0x80，执行系统调用
    int 0x80