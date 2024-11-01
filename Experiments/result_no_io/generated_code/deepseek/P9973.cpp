#include <stdio.h>
#include <string.h>

int main() {
    char s[201];
    fgets(s, sizeof(s), stdin);

    // 去掉可能的换行符
    s[strcspn(s, "\n")] = '\0';

    // 判断前19个字符是否与特定前缀匹配
    if (strlen(s) >= 19 && strncmp(s, "你说得对，但是", 19) == 0) {
        printf("AI\n");
    } else {
        printf("Human\n");
    }

    return 0;
}