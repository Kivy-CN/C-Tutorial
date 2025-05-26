// 包含标准输入输出库，提供printf、scanf、fopen等函数
#include <stdio.h>
// 包含字符串处理库，提供strcspn等字符串操作函数
#include <string.h>

// 程序主函数入口点
int main() {
    // 声明文件指针变量，用于操作文件
    FILE *file;
    // 声明整型变量，用于存储用户输入的序号
    int number;
    // 声明字符数组，用于存储用户输入的姓名，最大长度99个字符+1个结束符
    char name[100];
    // 声明字符变量，用于存储用户选择是否继续的输入
    char choice;
    
    // do-while循环开始，至少执行一次循环体
    do {
        // 向用户显示提示信息，要求输入序号
        printf("请输入序号: ");
        // 从标准输入读取一个整数，存储到number变量中
        scanf("%d", &number);
        
        // 清除输入缓冲区中残留的换行符，防止影响后续输入
        // getchar()逐个读取字符直到遇到换行符为止
        while(getchar() != '\n');
        
        // 向用户显示提示信息，要求输入姓名
        printf("请输入姓名: ");
        // 从标准输入读取一行字符串，最多读取99个字符，存储到name数组中
        fgets(name, sizeof(name), stdin);
        
        // 查找姓名字符串中第一个换行符的位置，并将其替换为字符串结束符
        // strcspn返回在name中第一个出现"\n"字符之前的字符数
        name[strcspn(name, "\n")] = '\0';
        
        // 以追加模式("a")打开名为"record.txt"的文件
        // 如果文件不存在，会自动创建；如果存在，新内容会追加到文件末尾
        file = fopen("record.txt", "a");
        
        // 检查文件是否成功打开，fopen失败时返回NULL
        if (file == NULL) {
            // 如果文件打开失败，输出错误信息
            printf("错误：无法打开或创建文件 record.txt\n");
            // 返回1表示程序异常退出
            return 1;
        }
        
        // 使用fprintf将格式化的数据写入文件
        // 写入格式：序号: [数字], 姓名: [姓名字符串]，然后换行
        fprintf(file, "序号: %d, 姓名: %s\n", number, name);
        
        // 关闭文件，释放文件资源，确保数据被正确写入磁盘
        fclose(file);
        
        // 向用户显示成功保存的确认信息
        printf("记录已成功保存到 record.txt 文件中！\n");
        
        // 询问用户是否要继续添加记录
        printf("是否继续添加记录？(y/n): ");
        // 读取用户输入的字符，空格跳过前导空白字符
        scanf(" %c", &choice);
        
    // 检查循环条件：如果用户输入'y'或'Y'，继续循环；否则退出循环
    } while (choice == 'y' || choice == 'Y');
    
    // 程序正常结束时显示的信息
    printf("程序结束，感谢使用！\n");
    // 返回0表示程序正常结束
    return 0;
}