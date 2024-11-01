#include <stdio.h>
#include <string.h>

void removeKdigits(char *num, int k) {
    int len = strlen(num);
    if (k == len) {
        num[0] = '0';
        return;
    }
    int stack[len];
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
        num[index++] = num[stack[i]];
    }
    num[index] = '\0';
}

int main() {
    char n[251];
    int k;
    scanf("%s %d", n, &k);
    removeKdigits(n, k);
    printf("%s\n", n);
    return 0;
}