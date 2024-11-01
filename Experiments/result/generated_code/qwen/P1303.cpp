#include <stdio.h>
#include <string.h>

#define MAXN 4005

void multiply(char *a, char *b, char *res) {
    int lenA = strlen(a), lenB = strlen(b);
    memset(res, '0', sizeof(res));
    for (int i = lenA - 1; i >= 0; --i) {
        for (int j = lenB - 1; j >= 0; --j) {
            int mul = (a[i] - '0') * (b[j] - '0');
            int pos1 = i + j, pos2 = i + j + 1;
            int sum = mul + res[pos2] - '0';
            res[pos1] += sum / 10;
            res[pos2] = (sum % 10) + '0';
        }
    }
}

int main() {
    char num1[MAXN], num2[MAXN], result[MAXN];
    scanf("%s %s", num1, num2);
    multiply(num1, num2, result);
    printf("%s\n", result);
    return 0;
}