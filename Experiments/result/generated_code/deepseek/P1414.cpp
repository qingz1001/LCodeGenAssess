#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MAXV 1000000

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int n;
    scanf("%d", &n);
    int abilities[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &abilities[i]);
    }

    int max_gcd[MAXN + 1] = {0};
    int count[MAXV + 1] = {0};

    for (int i = 0; i < n; i++) {
        for (int j = 1; j * j <= abilities[i]; j++) {
            if (abilities[i] % j == 0) {
                count[j]++;
                if (j != abilities[i] / j) {
                    count[abilities[i] / j]++;
                }
            }
        }
    }

    for (int i = 1; i <= MAXV; i++) {
        if (count[i] > 0) {
            for (int j = count[i]; j > 0; j--) {
                if (i > max_gcd[j]) {
                    max_gcd[j] = i;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d\n", max_gcd[i]);
    }

    return 0;
}