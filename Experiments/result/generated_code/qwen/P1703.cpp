#include <stdio.h>
#include <string.h>

void reverseSubstring(char *str, int start, int end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int main() {
    char key[100], plainText[1000];
    int M, a, b;

    scanf("%s", key);
    scanf("%s", plainText);
    scanf("%d", &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        reverseSubstring(plainText + a - 1, a - 1, b - 1);
    }

    printf("%s\n", plainText);

    return 0;
}