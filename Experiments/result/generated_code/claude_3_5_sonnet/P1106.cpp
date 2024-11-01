#include <stdio.h>
#include <string.h>

#define MAX_LEN 251

void removeDigits(char *num, int k) {
    int len = strlen(num);
    int top = 0;
    char stack[MAX_LEN];

    for (int i = 0; i < len; i++) {
        while (top > 0 && k > 0 && stack[top - 1] > num[i]) {
            top--;
            k--;
        }
        if (top < len - k) {
            stack[top++] = num[i];
        }
    }
    stack[top] = '\0';

    // 移除前导零
    int start = 0;
    while (start < top - 1 && stack[start] == '0') {
        start++;
    }

    printf("%s\n", &stack[start]);
}

int main() {
    char num[MAX_LEN];
    int k;

    scanf("%s", num);
    scanf("%d", &k);

    removeDigits(num, k);

    return 0;
}