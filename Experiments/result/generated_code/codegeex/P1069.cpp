#include <stdio.h>
#include <math.h>

// 函数：计算最大公约数
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

// 函数：计算最小公倍数
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

// 函数：计算质因数分解
void prime_factors(int n, int primes[], int *count) {
    int i = 0;
    while (n % 2 == 0) {
        primes[i++] = 2;
        n /= 2;
    }
    for (int j = 3; j <= sqrt(n); j += 2) {
        while (n % j == 0) {
            primes[i++] = j;
            n /= j;
        }
    }
    if (n > 2) {
        primes[i++] = n;
    }
    *count = i;
}

int main() {
    int N, m1, m2, M;
    scanf("%d", &N);
    scanf("%d %d", &m1, &m2);
    M = pow(m1, m2);

    int Si;
    int min_time = -1;
    for (int i = 0; i < N; i++) {
        scanf("%d", &Si);

        int primes[10000];
        int count;
        prime_factors(M, primes, &count);

        int max_time = 0;
        for (int j = 0; j < count; j++) {
            int time = 0;
            while (Si % primes[j] == 0) {
                Si /= primes[j];
                time++;
            }
            if (time > 0) {
                max_time = lcm(max_time, time);
            }
        }

        if (Si != 1) {
            max_time = -1;
        }

        if (min_time == -1 || (max_time != -1 && max_time < min_time)) {
            min_time = max_time;
        }
    }

    printf("%d\n", min_time);
    return 0;
}