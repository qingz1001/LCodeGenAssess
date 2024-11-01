#include <stdio.h>
#include <string.h>

#define MAX_LEN 251

void removeKdigits(char *num, int k, char *result) {
    int len = strlen(num);
    if (k == len) {
        result[0] = '0';
        result[1] = '\0';
        return;
    }

    int stack[MAX_LEN];
    int top = -1;

    for (int i = 0; i < len; ++i) {
        while (top != -1 && num[i] < num[stack[top]] && k > 0) {
            --top;
            --k;
        }
        stack[++top] = i;
    }

    int index = 0;
    for (int i = 0; i <= top; ++i) {
        if (index == 0 && num[stack[i]] == '0') continue;
        result[index++] = num[stack[i]];
    }

    if (index == 0) {
        result[0] = '0';
        result[1] = '\0';
    } else {
        result[index] = '\0';
    }
}

int main() {
    char num[MAX_LEN], result[MAX_LEN];
    int k;

    scanf("%s %d", num, &k);

    removeKdigits(num, k, result);

    printf("%s\n", result);

    return 0;
}