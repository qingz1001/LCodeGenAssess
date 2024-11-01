#include <stdio.h>
#include <math.h>

int g(int n, int k) {
    int count = 0;
    while (n >= k) {
        if (pow(k, round(log(n) / log(k))) == n) {
            count++;
        }
        k++;
    }
    return count;
}

double f(int n) {
    double result = 0.0;
    for (int i = 2; i <= n; i++) {
        result += (double)g(i, 2) / i;
    }
    return result;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        printf("%.14f\n", f(n));
    }
    return 0;
}