#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100005

int N;
long long M[MAXN];
long long sum[MAXN];

double check(double x) {
    double min_prefix = 0;
    double curr_prefix = 0;
    for (int i = 1; i < N - 1; i++) {
        curr_prefix += M[i] - x;
        if (curr_prefix < min_prefix)
            min_prefix = curr_prefix;
        if (sum[N] - sum[i+1] + min_prefix - (N-i-1)*x < 0)
            return 1;
    }
    return 0;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &M[i]);
        sum[i] = sum[i-1] + M[i];
    }

    double low = 0, high = sum[N];
    while (high - low > 1e-5) {
        double mid = (low + high) / 2;
        if (check(mid))
            high = mid;
        else
            low = mid;
    }

    printf("%.3f\n", low);
    return 0;
}