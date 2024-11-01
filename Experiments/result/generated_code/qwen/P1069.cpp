#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_M 30000

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int N, m1, m2;
    scanf("%d", &N);
    scanf("%d %d", &m1, &m2);
    long long M = (long long)m1 * m2;

    int S[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }

    int min_time = -1;
    for (int i = 0; i < N; i++) {
        long long cells = S[i];
        int time = 0;
        while (cells % M != 0) {
            cells *= S[i];
            time++;
        }
        if (min_time == -1 || time < min_time) {
            min_time = time;
        }
    }

    printf("%d\n", min_time);

    return 0;
}