#include <stdio.h>

int main() {
    char input[100];  // 定义字符数组存储输入内容

    printf("Hello, World!\n");

    // 键盘输入功能
    printf("请输入一段内容：");
    scanf("%s", input);  // 读取用户输入的字符串

    // 回显输入内容
    printf("你输入的内容是：%s\n", input);

    return 0;
}

