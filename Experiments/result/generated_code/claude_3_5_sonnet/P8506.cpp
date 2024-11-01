#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isTitle(char *line) {
    int i = 0;
    
    // 跳过开头的空白字符
    while (isspace(line[i])) i++;
    
    // 检查是否以#开头
    if (line[i] != '#') return 0;
    i++;
    
    // 跳过#后的空白字符
    while (isspace(line[i])) i++;
    
    // 检查#后是否有非空白字符
    return line[i] != '\0' && line[i] != '\n';
}

int main() {
    int n, count = 0;
    char line[101];  // 最多100个字符加上'\0'
    
    scanf("%d\n", &n);  // 读取行数，并消耗换行符
    
    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), stdin);
        if (isTitle(line)) count++;
    }
    
    printf("%d\n", count);
    return 0;
}