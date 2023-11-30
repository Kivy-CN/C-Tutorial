#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BASE64_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define BASE64_PAD_CHAR '='

void base64_encode(const char *input, char *output) {
    int i = 0, j = 0;
    unsigned char char_array_3[3], char_array_4[4];
    int in_len = strlen(input);
    int out_len = 0;

    // 遍历输入字符串，每3个字符一组，进行base64编码
    while (in_len--) {
        char_array_3[i++] = *(input++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            // 将base64编码字符串写入输出字符串
            for (i = 0; i < 4; i++) {
                output[out_len++] = BASE64_CHARS[char_array_4[i]];
            }
            i = 0;
        }
    }

    // 如果输入字符串长度不是3的倍数，则进行补0操作
    if (i) {
        for (j = i; j < 3; j++) {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        // 将base64编码字符串写入输出字符串
        for (j = 0; j < i + 1; j++) {
            output[out_len++] = BASE64_CHARS[char_array_4[j]];
        }

        // 将补0操作写入输出字符串
        while (i++ < 3) {
            output[out_len++] = BASE64_PAD_CHAR;
        }
    }
    output[out_len] = '\0';
}

int main() {
    char input[1000];
    printf("Enter a string to encode in base64: ");
    fgets(input, 1000, stdin);
    input[strcspn(input, "\n")] = 0;

    char encoded[1000];
    base64_encode(input, encoded);
    printf("Encoded string: %s\n", encoded);

    printf("Original string: %s\n", input);
    return 0;
}