// 包含标准输入输出库，提供printf、scanf、fopen等函数
#include <stdio.h>
// 包含字符串处理库，提供strcspn等字符串操作函数
#include <string.h>

// 程序主函数入口点
int main() {
    // 声明文件指针变量，用于操作文件
    FILE *file;
    // 声明字符数组，用于存储问题和答案，最大长度99个字符+1个结束符
    char question[100];
    char answer[100];
    char user_input[100];
    // 声明整型变量，用于记录答题次数
    int attempts = 0;
    const int max_attempts = 3;
    
    // 尝试打开result.txt文件进行读取，检查是否为第一次运行
    file = fopen("result.txt", "r");
    
    if (file == NULL) {
        // 第一次运行：文件不存在，需要创建问题和答案
        printf("欢迎！这是第一次运行，请创建一个问题和答案。\n");
        
        // 获取问题
        printf("请输入一个问题: ");
        fgets(question, sizeof(question), stdin);
        question[strcspn(question, "\n")] = '\0';
        
        // 获取答案
        printf("请输入这个问题的答案: ");
        fgets(answer, sizeof(answer), stdin);
        answer[strcspn(answer, "\n")] = '\0';
        
        // 以写入模式创建result.txt文件
        file = fopen("result.txt", "w");
        if (file == NULL) {
            printf("错误：无法创建文件 result.txt\n");
            return 1;
        }
        
        // 将问题和答案保存到文件中
        fprintf(file, "%s\n%s\n", question, answer);
        fclose(file);
        
        printf("问题和答案已保存到 result.txt 文件中！\n");
        printf("程序结束，下次运行时将进行答题测试。\n");
        return 1;  // 修改：第一次运行返回1
        
    } else {
        // 第二次及以后运行：文件存在，进行答题测试
        // 从文件中读取问题和答案
        fgets(question, sizeof(question), file);
        question[strcspn(question, "\n")] = '\0';
        
        fgets(answer, sizeof(answer), file);
        answer[strcspn(answer, "\n")] = '\0';
        
        fclose(file);
        
        printf("欢迎回来！请回答以下问题：\n");
        
        // 答题循环，最多允许3次尝试
        do {
            attempts++;
            printf("\n问题：%s\n", question);
            printf("请输入你的答案（第 %d 次尝试，共 %d 次机会）: ", attempts, max_attempts);
            
            fgets(user_input, sizeof(user_input), stdin);
            user_input[strcspn(user_input, "\n")] = '\0';
            
            // 比较用户输入和正确答案（不区分大小写）
            if (strcasecmp(user_input, answer) == 0) {
                printf("恭喜！答对了！🎉\n");
                printf("程序结束，感谢参与！\n");
                return 0;  // 只有这里返回0
            } else {
                if (attempts < max_attempts) {
                    printf("答案错误，请重试。\n");
                } else {
                    printf("答案错误。已用完所有 %d 次机会。\n", max_attempts);
                    printf("正确答案是：%s\n", answer);
                    printf("程序结束。\n");
                }
            }
            
        } while (attempts < max_attempts);
    }
    
    return 1;  // 修改：所有其他情况都返回1
}