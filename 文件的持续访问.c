#include <stdio.h>
#include <string.h>

int main() {
    FILE *file;
    int number;
    char name[100];
    char choice;
    
    do {
        // 提示用户输入序号
        printf("请输入序号: ");
        scanf("%d", &number);
        
        // 清除输入缓冲区中的换行符
        while(getchar() != '\n');
        
        // 提示用户输入姓名
        printf("请输入姓名: ");
        fgets(name, sizeof(name), stdin);
        
        // 去除姓名末尾的换行符
        name[strcspn(name, "\n")] = '\0';
        
        // 以追加模式打开文件，如果文件不存在会自动创建
        file = fopen("record.txt", "a");
        
        // 检查文件是否成功打开
        if (file == NULL) {
            printf("错误：无法打开或创建文件 record.txt\n");
            return 1;
        }
        
        // 将序号和姓名写入文件
        fprintf(file, "序号: %d, 姓名: %s\n", number, name);
        
        // 关闭文件
        fclose(file);
        
        printf("记录已成功保存到 record.txt 文件中！\n");
        
        // 询问是否继续添加记录
        printf("是否继续添加记录？(y/n): ");
        scanf(" %c", &choice);
        
    } while (choice == 'y' || choice == 'Y');
    
    printf("程序结束，感谢使用！\n");
    return 0;
}