#include <stdio.h>
#include <string.h>

#define MOD 1000000007

void multiply(char *a, char *b, char *res) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    memset(res, '0', sizeof(char) * (len_a + len_b));
    for (int i = 0; i < len_a; i++) {
        for (int j = 0; j < len_b; j++) {
            int mul = (a[i] - '0') * (b[j] - '0');
            int sum = mul + res[i + j] - '0';
            res[i + j] = (sum % 10) + '0';
            res[i + j + 1] += sum / 10;
        }
    }
}

void power(char *base, int exp, char *result) {
    strcpy(result, "1");
    while (exp > 0) {
        if (exp % 2 == 1) {
            multiply(result, base, result);
        }
        multiply(base, base, base);
        exp /= 2;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    char base[202];
    char result[202];
    sprintf(base, "%d", 3);
    power(base, n - 1, result);
    printf("%s\n", result);
    return 0;
}