#include <stdio.h>
#include <string.h>

#define MAXN 101
#define MAXD 1000

void multiply(int res[], int num) {
    int carry = 0;
    for (int i = 0; i < MAXD; i++) {
        int temp = res[i] * num + carry;
        res[i] = temp % 10;
        carry = temp / 10;
    }
}

void add(int res[], int num) {
    int carry = num;
    for (int i = 0; i < MAXD; i++) {
        int temp = res[i] + carry;
        res[i] = temp % 10;
        carry = temp / 10;
        if (carry == 0) break;
    }
}

void calculate(int n, int res[]) {
    int f[MAXN][MAXD];
    memset(f, 0, sizeof(f));
    f[1][0] = 1;

    for (int i = 2; i <= n; i++) {
        memset(res, 0, sizeof(int) * MAXD);
        for (int j = 1; j < i; j++) {
            multiply(f[j], 3);
            add(res, f[j]);
        }
        multiply(res, i - 1);
        add(res, 2);
        memcpy(f[i], res, sizeof(int) * MAXD);
    }

    memcpy(res, f[n], sizeof(int) * MAXD);
}

int main() {
    int n;
    scanf("%d", &n);

    int res[MAXD];
    memset(res, 0, sizeof(res));
    calculate(n, res);

    int start = MAXD - 1;
    while (start > 0 && res[start] == 0) start--;
    for (int i = start; i >= 0; i--) {
        printf("%d", res[i]);
    }
    printf("\n");

    return 0;
}