//读取长字符，并一个一个显示 ASCII 码。
#include <stdio.h>
#define MAX_STRING_LENGTH 65535 // 最大字符串长度

int main(){
  char s[MAX_STRING_LENGTH];
  printf("请输入长度小于 %d 的任意字符：",MAX_STRING_LENGTH);
  scanf("%s",s);    // 读取字符串。
  for(int i = 0; s[i]; i++){
    printf("%c 的 ASCII 码为:%d\n",s[i],s[i]);
  }
}