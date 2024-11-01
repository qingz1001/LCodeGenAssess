#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int min_time_to_split(int S, int m1, int m2) {
    int M = pow(m1, m2);
    if (S % m1 == 0) {
        return 0;
    }
    int time = 0;
    while (S % m1 != 0) {
        S *= S;
        time++;
        if (S > M) {
            return -1;
        }
    }
    return time;
}

int main() {
    int N, m1, m2;
    scanf("%d", &N);
    scanf("%d %d", &m1, &m2);

    int *S = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }

    int min_time = -1;
    for (int i = 0; i < N; i++) {
        int time = min_time_to_split(S[i], m1, m2);
        if (time != -1 && (min_time == -1 || time < min_time)) {
            min_time = time;
        }
    }

    printf("%d\n", min_time);

    free(S);
    return 0;
}