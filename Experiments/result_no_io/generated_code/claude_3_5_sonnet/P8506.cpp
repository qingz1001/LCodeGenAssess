#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 10
#define MAX_LENGTH 100

int isTitle(char *line) {
    int i = 0;
    
    // 跳过开头的空白字符
    while (isspace(line[i])) {
        i++;
    }
    
    // 检查是否以#开头
    if (line[i] != '#') {
        return 0;
    }
    
    i++;
    
    // 跳过#后的空白字符
    while (isspace(line[i])) {
        i++;
    }
    
    // 检查#后是否有非空白字符
    return line[i] != '\0' && line[i] != '\n';
}

int main() {
    int n, count = 0;
    char text[MAX_LINES][MAX_LENGTH];
    
    scanf("%d\n", &n);
    
    for (int i = 0; i < n; i++) {
        fgets(text[i], MAX_LENGTH, stdin);
    }
    
    for (int i = 0; i < n; i++) {
        if (isTitle(text[i])) {
            count++;
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}