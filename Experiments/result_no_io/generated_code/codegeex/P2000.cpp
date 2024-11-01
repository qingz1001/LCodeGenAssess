#include <stdio.h>
#include <string.h>

int main() {
    char n[100005];
    scanf("%s", n);
    int len = strlen(n);
    int kkksc03 = 1, lzn = 1;

    for (int i = 0; i < len; i++) {
        int num = n[i] - '0';
        kkksc03 = (kkksc03 * (num + 1)) % 10;
        lzn = (lzn * (num + 1)) % 10;
    }

    int result = (kkksc03 + lzn) % 10;
    printf("%d\n", result);

    return 0;
}