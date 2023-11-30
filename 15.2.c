#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BASE64_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define BASE64_PAD_CHAR '='

// 编码函数，参数input为输入字符串，output为输出字符串，shift为偏移量
void encode(char *input, char *output, int shift) {
    int i = 0;
    while (input[i] != '\0') {
        if (isalpha(input[i])) {
            char c = input[i];
            if (isupper(c)) {
                c = tolower(c);
            }
            int index = strchr(BASE64_CHARS, c) - BASE64_CHARS;
            int shifted_index = (index + shift) % strlen(BASE64_CHARS);
            output[i] = BASE64_CHARS[shifted_index];
        } else {
            output[i] = input[i];
        }
        i++;
    }
    output[i] = '\0';
}

int main() {
    // 定义一个字符串数组，用于存储输入的字符串
    char input[1000];
    // 打印提示信息，让用户输入字符串
    printf("Enter a string to encode: ");
    // 读取用户输入的字符串
    fgets(input, 1000, stdin);
    // 将换行符替换为'\0'
    input[strcspn(input, "\n")] = 0;

    // 定义一个变量，用于存储偏移量
    int shift;
    // 打印提示信息，让用户输入偏移量
    printf("Enter a shift value: ");
    // 读取用户输入的偏移量
    scanf("%d", &shift);

    // 定义一个字符串数组，用于存储编码后的字符串
    char encoded[1000];
    // 调用encode函数，对输入的字符串进行编码，并将编码后的字符串存储到encoded数组中
    encode(input, encoded, shift);
    // 打印编码后的字符串
    printf("Encoded string: %s\n", encoded);

    // 定义一个字符串数组，用于存储解码后的字符串
    char decoded[1000];
    // 调用encode函数，对编码后的字符串进行解码，并将解码后的字符串存储到decoded数组中
    encode(encoded, decoded, -shift);
    // 打印解码后的字符串
    printf("Original string: %s\n", decoded);
    return 0;
}