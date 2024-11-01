#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int magic(int n) {
    char str[20];
    sprintf(str, "%d", n);
    int len = strlen(str);
    char result[20];
    int idx = 0;
    for (int i = 0; i < len - 1; i++) {
        int diff = abs(str[i] - str[i + 1]);
        result[idx++] = diff + '0';
    }
    result[idx] = '\0';
    return atoi(result);
}

int magic_fingerprint(int n) {
    while (n >= 10) {
        n = magic(n);
    }
    return n;
}

int main() {
    int A, B;
    scanf("%d", &A);
    scanf("%d", &B);

    int count = 0;
    for (int i = A; i <= B; i++) {
        if (magic_fingerprint(i) == 7) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}