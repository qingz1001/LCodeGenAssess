#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    int n, a[10];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    for (int m = 0; m < n; m++) {
                        for (int o = 0; o < n; o++) {
                            if (a[i] == 0 || a[j] == 0 || a[k] == 0 || a[l] == 0 || a[m] == 0 || a[o] == 0) continue;
                            int num1 = a[i] * 100 + a[j] * 10 + a[k];
                            int num2 = a[l] * 10 + a[m];
                            int num3 = a[i] * a[m] * 100 + a[j] * a[m] * 10 + a[k] * a[m];
                            int num4 = a[i] * a[l] * 100 + a[j] * a[l] * 10 + a[k] * a[l];
                            int num5 = a[i] * a[o] * 1000 + a[j] * a[o] * 100 + a[k] * a[o] * 10;
                            if (num3 + num4 == num5 && is_prime(num1) && is_prime(num2) && is_prime(num5)) {
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}