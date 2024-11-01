#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char S[101];
    scanf("%s", S);
    
    int len = strlen(S);
    char result[101];
    int result_index = 0;
    
    // 跳过开头的 '[' 和 'A' 到 'Z' 的部分
    int i = 1;
    while (isupper(S[i])) {
        result[result_index++] = tolower(S[i]);
        i++;
    }
    
    // 跳过 ']' 和后面的固定字符串
    while (S[i] != ']') {
        i++;
    }
    i++;
    while (S[i] != '\0') {
        i++;
    }
    
    result[result_index++] = '/';
    for (int j = 0; j < result_index - 1; j++) {
        result[result_index++] = result[j];
    }
    result[result_index] = '\0';
    
    printf("%s\n", result);
    
    return 0;
}