#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define INF INT_MAX

long long n;
int k[1000001];
int min_k[1000001];

int calculate_k(long long num) {
    if (num <= 1000000 && k[num] != -1) return k[num];
    long long sqrt_num = (long long)sqrt(num);
    int min_k_value = INF;
    for (long long i = sqrt_num; i >= 1; i--) {
        int temp_k = calculate_k(num - i * i);
        if (temp_k != INF) {
            min_k_value = (int)i;
            break;
        }
    }
    if (num <= 1000000) k[num] = min_k_value;
    return min_k_value;
}

int main() {
    scanf("%lld", &n);

    for (int i = 0; i <= 1000000; i++) {
        k[i] = -1;
        min_k[i] = INF;
    }
    k[0] = 0;

    for (int i = 1; i <= 1000000; i++) {
        k[i] = calculate_k(i);
        if (k[i] != INF) {
            min_k[k[i]] = i;
        }
    }

    int k_n = calculate_k(n);
    if (k_n == INF) {
        printf("-\n");
        return 0;
    }

    int count_heavy = 0;
    for (int i = 1; i <= n; i++) {
        if (k[i] != INF && min_k[k[i]] < i) {
            count_heavy++;
        }
    }

    printf("%d %d\n", k_n, count_heavy);
    return 0;
}