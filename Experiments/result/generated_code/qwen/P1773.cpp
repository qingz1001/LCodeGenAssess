#include <stdio.h>
#include <string.h>

int main() {
    char num[1001];
    int m, len;
    scanf("%s %d", num, &m);
    len = strlen(num);

    int min_x = m - 1;
    int max_x = 1;
    int min_k = 0;
    int max_k = 0;

    for (int i = 0; i < len; i++) {
        int digit = num[i] - '0';
        if (digit == 1) {
            continue;
        }
        if (digit <= m) {
            min_x = 0;
            min_k = 0;
            break;
        }
        if (digit > max_x) {
            max_x = digit;
            max_k = 1;
        }
    }

    printf("%d %d %d %d\n", min_x, min_k, max_x, max_k);
    return 0;
}